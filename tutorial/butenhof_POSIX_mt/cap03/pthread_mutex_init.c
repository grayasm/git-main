/*
 * int pthread_mutex_init(pthread_mutex_t* mutex,
 *                        const pthread_mutex_attr_t* attr);
 *
 * pthread_mutex_init - function shall initialize the mutex referenced by mutex
 *                      with attributes specified by attr. If attr is NULL default
 *                      is used. Upon successful initialization, the state of
 *                      the mutex becomes initialized and unlocked.
 *                      Mutex must not be copied otherwise behavior is undefined.
 *                      If successful function shall return zero.
 */



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"

const int MAX_THREADS=3;
void* thread_routine(void*);
pthread_mutex_t mutex;


int main(int argc, char** argv)
{
	int err;
	long i;
	pthread_t thrds[MAX_THREADS];

	err = pthread_mutex_init(&mutex, NULL);
	if(err)
		err_abort(err, "pthread_mutex_init");

	for(i=0; i < MAX_THREADS; ++i)
	{
		err = pthread_create(&thrds[i],
		                     NULL,
		                     thread_routine,
		                     (void*)i);

		if(err)
			err_abort(err, "pthread_create");

		printf("\nLaunched thread: %d", i);
	}


	for(i=0; i < MAX_THREADS; ++i)
	{
		void* retval;
		err = pthread_join(thrds[i], &retval);
		if(err)
			err_abort(err, "pthread_join");
	}

	err = pthread_mutex_destroy(&mutex);
	if(err)
		err_abort(err, "pthread_mutex_destroy");

	printf("\nExit success\n\n");
	return EXIT_SUCCESS;
} // main

void* thread_routine(void* arg)
{
	int err;


	err = pthread_mutex_lock(&mutex);
	if(err)
		err_abort(err, "pthread_mutex_lock");

	printf("\n\tMutex lock   th: %d", (long)arg);
	fflush(stdout);

	sleep(3);

	printf("\n\tMutex unlock th: %d", (long)arg);
	fflush(stdout);

	err = pthread_mutex_unlock(&mutex);
	if(err)
		err_abort(err, "pthread_mutex_unlock");

	return arg;
}
