/*
  Condition variable, how it works in a simple diagram.

+--------------------------------------------------+
       main thread       kernel          2nd thread
+--------------------------------------------------+
       mutex init
       cond  init

       mutex LOCK
       [value=-1]
       create thread
       cond  wait -->   mutex UNLOCK
                                         mutex LOCK
                                         [value=100]
                                         cond signal
       (cannot wake                      working on smth.
       up because the
       mutex is still
       locked in 2nd
       thread)
                        mutex LOCK  <--  mutex UNLOCK
       woken up                          thread exit
       mutex UNLOCK

       join 2nd thread

       cond destroy
       mutex destroy
       return
+--------------------------------------------------+
*/


#include <pthread.h>
#include "errors.h"

typedef struct data_tag
{
	pthread_mutex_t    mutex;
	pthread_cond_t     cond;
	int                value;
} data_t;


void* write_routine(void* arg)
{
	int err;
	data_t* data = (data_t*) arg;


	/* Lock the mutex to change variable safely.
	 * Main thread cannot wake up accidentally if the mutex is
	 * locked. Other thread also needs to aquire a lock to change the value.
	 */
	err= pthread_mutex_lock(&data->mutex);
	if(err) err_abort(err, "thread mutex lock");
	printf("\n\tThread: Mutex locked");

	/* change the value, (in book this is a "predicate") */
	data->value = rand()%100;


	/* pthread_cond_signal will signal the condition to the main thread,
	 * HOWEVER it will not wake up until the mutex is not unlocked again.
	 */
	err = pthread_cond_signal(&data->cond);
	if(err) err_abort(err, "thread condition signal");
	printf("\n\tThread: Condition signaled");

	sched_yield();

	printf("\n\tThread: sleep 2 sec");
	sleep(2);

	/* Unlock the mutex. The kernel needs to lock the mutex before
	 * waking up the main thread.
	 */
	err = pthread_mutex_unlock(&data->mutex);
	if(err) err_abort(err, "thread mutex unlock");
	printf("\n\tThread: Mutex unlocked");

	sched_yield();
	printf("\n\tThread: sleep 2 sec, and then print exit msg.");
	sleep(2);

	printf("\n\tThread: exited");
	return arg;
}


int main(int argc, char** argv)
{
	int err;
	data_t* data;
	void* retval;
	pthread_t thread;

	// ----- first part -----
	data = (data_t*) malloc(sizeof(data_t));
	if(!data) errno_abort("malloc data_t");

	err = pthread_mutex_init(&data->mutex, NULL);
	if(err) err_abort(err, "mutex init");

	err = pthread_cond_init(&data->cond, NULL);
	if(err) err_abort(err, "condition init");

	// ----- middle part -----
	data->value = -1;


	err = pthread_mutex_lock(&data->mutex);
	if(err) err_abort(err, "mutex lock");
	printf("\nMutex locked");


	err = pthread_create(&thread, NULL, write_routine, data);
	if(err) err_abort(err, "create thread");
	printf("\nLaunched thread");


	printf("\nWait for condition");
	err = pthread_cond_wait(&data->cond, &data->mutex);
	if(err) err_abort(err, "condition wait");

	printf("\nWoken up, condition signaled");

	// ----- last part -----
	if(data->value != -1)
		printf("\nData has changed");
	else
		printf("\nData hasn't changed");

	err = pthread_mutex_unlock(&data->mutex);
	if(err) err_abort(err, "mutex unlock");
	printf("\nMutex unlocked");


	err = pthread_join(thread, &retval);
	if(err) err_abort(err, "join thread");
	printf("\nThread finished, will clean up now.");


	err = pthread_cond_destroy(&data->cond);
	if(err) err_abort(err, "condition destroy");

	err = pthread_mutex_destroy(&data->mutex);
	if(err) err_abort(err, "mutex destroy");
	free(data);

	printf("\nAll cleaned up, exit OK\n");
	return 0;
}
