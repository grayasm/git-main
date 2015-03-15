/*
 * int  pthread_mutex_timedlock (pthread_mutex_t* mutex,
 *                               const struct timespec* abs_timeout);
 *
 *      Function shall lock the mutex or shall block until the mutex becomes
 *      available similar with pthread_mutex_lock() or the timeout expires.
 *
 *      If the Timers option is supported, the timeout shall be based on
 *      CLOCK_REALTIME clock, otherwise on system clock as returned by time()
 *
 *
 *      If successful, function shall return zero; otherwise, an error number
 *      shall indicate the error.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"


#define MAX_THREADS 4
void* start_routine(void*);
pthread_mutex_t mutex;


int main(int argc, char** argv)
{
	int err;
	long i;
	pthread_t thrds[MAX_THREADS];

	// initialized the mutex with default attributes
	pthread_mutex_init(&mutex, NULL);


	// launch all threads
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


	// wait for the thread to finish
	for(i=0; i < MAX_THREADS; ++i)
	{
		void* retval;
		err = pthread_join(thrds[i], &retval);
		if(err)
			err_abort(err, "pthread_join");
		printf("\nThread %d returned %d", i, (long)retval);
	}


	// clear mutex
	err = pthread_mutex_destroy(&mutex);
	if(err)
		err_abort(err, "pthread_mutex_destroy");

	// exit
	printf("\nExiting ...\n");

	return EXIT_SUCCESS;
}



// each thread starts here
void* start_routine(void* arg)
{
	int err;
	long i = (long)arg;

	// attempt a timed lock for about (max) 3 seconds
	struct timespec ts;
	ts.tv_sec = time(NULL) + 2;
	ts.tv_nsec = 0;

	while((err = pthread_mutex_timedlock(&mutex, &ts)) != 0)
	{
		if(err != ETIMEDOUT)
			err_abort(err, "pthread_mutex_timedlock");

		printf("\n\t\tRetry \"timedlock\" in thread %d", i);


		// attempt a timed lock for about (max) 3 seconds
		ts.tv_sec = time(NULL) + 2;
	}

	printf("\n\tMutex locked   in thread %d", i);
	sleep(1);
	printf("\n\tMutex unlocked in thread %d", i);

	// allow next thread to acquire a lock on the mutex
	err = pthread_mutex_unlock(&mutex);
	if(err)
		err_abort(err, "pthread_mutex_unlock");

	return arg;
}
