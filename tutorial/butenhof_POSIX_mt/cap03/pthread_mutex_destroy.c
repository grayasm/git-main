/*
 * pthread_mutex_destroy - destory a mutex
 *
 * int pthread_mutex_destroy(pthread_mutex_t* mutex);
 *
 *     Function shall destroy the mutex object referenced by mutex. The mutex
 *     object becomes in effect uninitialized. An implementation may cause
 *     pthread_mutex_destroy() to set the mutex to an invalid value.
 *
 *     A destroyed mutex object can be reinitialized using pthread_mutex_init().
 *     Referencing a destroyed mutex results in undefined behavior.
 *
 *     If successful the function shall return zero.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

#define MAX_THREADS 5

void* start_routine(void*);
pthread_mutex_t gMutex;

int main(int argc, char** argv)
{
	int err;
	long i;
	pthread_t thrds[MAX_THREADS];

	err = pthread_mutex_init(&gMutex, NULL);
	if(err)
		err_abort(err, "pthread_mutex_init");


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

	err = pthread_mutex_destroy(&gMutex);
	if(err)
		err_abort(err, "pthread_mutex_destroy");



	printf("\nExit now...\n");

	return EXIT_SUCCESS;
} // main


void* start_routine(void* arg)
{
	int err;

	err = pthread_mutex_lock(&gMutex);
	if(err)
		err_abort(err, "pthread_mutex_lock");
	printf("\n\tMutex locked, th %d", (long)arg);

	sleep(1);

	printf("\n\tMutex unlock, th %d", (long)arg);

	err = pthread_mutex_unlock(&gMutex);
	if(err)
		err_abort(err, "pthread_mutex_unlock");

	return arg;
}
