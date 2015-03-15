/*
 * If you create a set of threads to "subcontract" some function,
 * say a parallel arithmetic operation, and the "contractor" is canceled
 * while the function is in progress, you could "pass on" the cancellation
 * to each subcontractor thread, letting them handle their own termination
 * independently.
 */
#include <pthread.h>
#include "errors.h"


#define THREADS 5

/* Structure that defines the threads in a "team". */
typedef struct team_tag
{
    int             join_i;             /* join index */
    pthread_t       workers[THREADS];   /* thread identifiers */
} team_t;

/* Start routine for worker threads. They loop waiting for a
 * cancellation request.
 */
void* worker_routine(void* arg)
{
    int counter;

    for (counter = 0; ; counter++)
        if ((counter % 1000) == 0)
            pthread_testcancel ();
}


/* Cancellation cleanup handler for the contractor thread. It
 * will cancel and detach each worker in the team.
 */
void cleanup(void* arg)
{
    team_t*  team = (team_t*) arg;
    int count, err;

    for (count = team->join_i; count < THREADS; count++)
    {
        err = pthread_cancel(team->workers[count]);
        if (err) err_abort(err, "Cancel worker");

        err = pthread_detach(team->workers[count]);
        if (err) err_abort(err, "Detach worker");

        printf("Cleanup: canceled %d\n", count);
    }
}


/* Thread start routine for the contractor. It creates a team of
 * worker threads, and then joins with them. When canceled,
 * the cleanup handler will cancel and detach the remaining threads.
 */
void* thread_routine(void* arg)
{
    team_t team;
    int count;
    void* result;
    int err;

    for (count = 0; count < THREADS; ++count)
    {
        err = pthread_create(&team.workers[count], NULL, worker_routine, NULL);
        if (err) err_abort(err, "Create worker");
    }

    pthread_cleanup_push(cleanup, (void*) &team);

    for (team.join_i = 0; team.join_i < THREADS; team.join_i++)
    {
        err = pthread_join(team.workers[team.join_i], &result);
        if (err) err_abort(err, "Join worker");
    }

    pthread_cleanup_pop(0);
    return NULL;
}


int main (int argc, char** argv)
{
    pthread_t thread_id;
    int err;

    err = pthread_create(&thread_id, NULL, thread_routine, NULL);
    if (err) err_abort (err, "Create team");
    sleep(5);
    printf("Cancelling ...\n");
    err = pthread_cancel(thread_id);
    if(err) err_abort(err, "Cancel team");
    err = pthread_join(thread_id, NULL);
    if(err) err_abort(err, "Join team");
    return 0;
}
