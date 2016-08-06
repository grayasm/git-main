/*
 * int pthread_mutex_trylock(pthread_mutex_t* mutex);
 *
 *     Function shall be equivalent to pthread_mutex_lock(), except that if the
 *     mutex object referenced by mutex is currently locked (by the thread,
 *     including the current thread), the call shall return immediately.
 *
 *     If the mutex type is PTHREAD_MUTEX_RECURSIVE and the mutex is currently
 *     owned by the calling thread, the mutex lock count shall be incremented by
 *     one and the pthread_mutex_trylock() function shall immediately shall
 *     return success.
 *
 *     If a lock on the mutex object is acquired the function shall return zero,
 *     otherwise an error number to indicate the error.
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"


#define MAX_THREADS 4
void* start_routine(void*);
pthread_mutex_t gMutex;


int main(int argc, char** argv)
{
	int err;
	long i;
	pthread_t thrds[MAX_THREADS];

	/*
	 * For more explanations on mutex types see man pthread_mutex_lock or
	 * sample pthred_mutex_lock.c in this location.
	 * However this _ERRORCHECK type does not influence our sample.
	 */
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	pthread_mutex_init(&gMutex, &attr);

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
		printf("\nThread %d returned %d", i, (long) retval);
	}


	/* clean up resources */
	err = pthread_mutex_destroy(&gMutex);
	if(err)
		err_abort(err, "pthread_mutex_destroy");

	err = pthread_mutexattr_destroy(&attr);
	if(err)
		err_abort(err, "pthread_mutexattr_destroy");


	printf("\nExit now...\n");
	return EXIT_SUCCESS;
}


void* start_routine(void* arg)
{
	int err;

	/* Infamous BUSY LOOP while trying to aquire a lock on the mutex */
	while( pthread_mutex_trylock(&gMutex) )
	{
		printf("\n\tFailed trylock by thread %d", (long)arg);
		sleep(1);
	}

	printf("\n\t\tLocked  by  thread %d", (long) arg);
	/* slowing down will make other threads fail the trylock attempt */
	sleep(1);

	printf("\n\t\tUnlocked by thread %d", (long) arg);
	err = pthread_mutex_unlock(&gMutex);
	if(err)
		err_abort(err, "pthread_mutex_unlock");

	return arg;
}
