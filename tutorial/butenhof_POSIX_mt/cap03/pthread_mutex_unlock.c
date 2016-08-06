/*
 * int pthread_mutex_unlock(pthread_mutex_t* mutex)
 *
 *     The function shall release the mutex object refereced by mutex.
 *     The scheduling policy shall determine which thread shall aquire the mutex.
 *
 *     In case of PTHREAD_MUTEX_RECURSIVE mutexes, the mutex shall become
 *     available when the count reaches zero and the calling thread no longer
 *     has any locks on this mutex.
 *     If a signal is delivered to a thread waiting for a mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"


#define MAX_THREADS 3
void* start_routine(void*);
pthread_mutex_t gMutex;


int main(int argc, char** argv)
{
	int err;
	long i;
	pthread_t thrds[MAX_THREADS];

	/* for error checking do:
	 * if(err) err_abort(err, "pthread_mutex ...");
	 */
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
	pthread_mutex_init(&gMutex, NULL);

	for(i=0; i < MAX_THREADS; ++i)
	{
		err = pthread_create(&thrds[i],
		                     NULL,
		                     start_routine,
		                     (void*)i);
		if(err)
			err_abort(err, "pthread_create");
		printf("\nLaunched thread %d", i);
	}


	for(i=0; i < MAX_THREADS; ++i)
	{
		void* retval;
		err = pthread_join(thrds[i], &retval);
		if(err)
			err_abort(err, "pthread_join");

		printf("\nFinished thread %d", i);
	}


	/* for error checking see above */
	/* clean up Mutex and its Attributes resources */
	pthread_mutex_destroy(&gMutex);
	pthread_mutexattr_destroy(&attr);


	printf("\nExit now ...\n");
	return EXIT_SUCCESS;
} // main


void* start_routine(void* arg)
{
	pthread_mutex_lock(&gMutex);
	printf("\n\tMutex locked thread   %d", (long)arg);
	fflush(stdout);

	sleep(1);

	printf("\n\tMutex unlocked thread %d", (long)arg);
	fflush(stdout);
	pthread_mutex_unlock(&gMutex);

	return arg;
}
