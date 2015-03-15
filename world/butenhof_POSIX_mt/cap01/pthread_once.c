/*
 * In this sample MAX_THREADS threads would attempt to call
 * the function: void called_once(), which is Pthreads protected by
 * pthread_once_t variable.
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "errors.h"


#define MAX_THREADS 4
pthread_once_t once_control = PTHREAD_ONCE_INIT;

void called_once()
{
	printf("\n\tInit routine should get called only 1 time!");
}

void* start_routine(void* arg)
{
	int err;

	err = pthread_once(&once_control, called_once);
	if(err) err_abort(err, "Once init");
	printf("\n\tRunning thread %d", (long)arg);
	return arg;
}



int main(int argc, char** argv)
{
	int err;
	long i;
	void* retval;
	pthread_t  thrds[MAX_THREADS];

	for(i = 0; i < MAX_THREADS; ++i)
	{
		err = pthread_create(&thrds[i], NULL, start_routine, (void*)i);
		if(err) err_abort(err, "Create thread");

		printf("\nCreated thread %d", i);
	}

	for(i = 0; i < MAX_THREADS; ++i)
	{
		err = pthread_join(thrds[i], &retval);
		if(err) err_abort(err, "Join thread");

		printf("\nJoined thread %d , retval %d", i, (long)retval);
	}

	printf("\nExit OK\n");
	return EXIT_SUCCESS;
}
