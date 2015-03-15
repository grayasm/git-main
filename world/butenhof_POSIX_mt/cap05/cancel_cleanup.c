/* 
 * Each thread may be considered to have a stack of active cleanup handler.
 * Cleanup handlers are added to the stack by calling pthread_cleanup_push,
 * and the most recently added cleanup handler is removed by calling
 * pthread_cleanup_pop.
 * When the thread is CANCELED or when it EXITS by calling pthread_exit,
 * Pthreads calls each active cleanup handler in turn (pops all from the stack).
 */
#include <pthread.h>
#include "errors.h"

#define THREADS 5

/* Control structure shared by the test threads, containing
 * the synchronization and invariant data.
 */
typedef struct control_tag
{
	int					counter, busy;
	pthread_mutex_t		mutex;
	pthread_cond_t		cv;
} control_t;


control_t control = 
{0, 1, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

/* This routine is installed as the cancellation cleaup
 * handler around the cancelable condition wait. It will
 * be called by the system when the thread is canceled.
 */
void cleanup_handler(void* arg)
{
	control_t* st = (control_t*) arg;
	int err;
	
	st->counter--;
	printf("cleanup handler: counter == %d\n", st->counter);
	err = pthread_mutex_unlock(&st->mutex);
	if(err) err_abort(err, "Unlock cleanup handler");
}


/* Multiple threads are created running this routine (controlled
 * by the THREADS macro). They maintain a "counter" invariant,
 * which expresses the number of running threads. They specify a
 * nonzero value to pthread_cleanup_pop to run the same
 * "finalization" action when cancellation does not occur.
 */
void* thread_routine(void* arg)
{
	int err;

	pthread_cleanup_push(cleanup_handler, (void*) &control);
	
	err = pthread_mutex_lock(&control.mutex);
	if (err) err_abort(err, "Mutex lock");
	control.counter++;
	
	while (control.busy)
	{
		err = pthread_cond_wait(&control.cv, &control.mutex);
		if (err) err_abort(err, "Wait on condition");
	}
	
	pthread_cleanup_pop(1);
	return NULL;
}


int main (int argc, char** argv)
{
	pthread_t  thread_id[THREADS];
	int count;
	void* result;
	int err;
	
	for (count = 0; count < THREADS; ++count)
	{
		err = pthread_create(&thread_id[count], NULL, thread_routine, NULL);
		if (err) err_abort(err, "Create thread");
	}
	
	sleep(2);
	
	for (count = 0; count < THREADS; ++count)
	{
		err = pthread_cancel(thread_id[count]);
		if (err) err_abort(err, "Cancel thread");
		
		err = pthread_join(thread_id[count], &result);
		if (err) err_abort(err, "Join thread");
		
		if (result == PTHREAD_CANCELED)
			printf("thread %d canceled\n", count);
		else
			printf("thread %d was not canceled\n", count);
	}
	
	return 0;
}





























