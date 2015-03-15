/*
 * This is written by me and pthread_cleanup_push is from manual :)
 * 
 * pthread_cleanup_pop - pop thread cancellation clean-up handlers
 *
 * void pthread_cleanup_pop(int execute);
 *      Function removes the routine at the top of the stack of clean-up
 *      handlers, and optionally executes it if execute is nonzero.
 *
 *      A cancellation clean-up handler is popped from the stack and executed
 *      in the following circumstances:
 *
 *      1) thread is canceled - all stacked clean-up handlers are executed;
 *      2) pthread_exit but NOT for return - same as (1)
 *      3) pthread_cleanup_pop(non_zero) - top stacked handler fcnt executed;
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

// one thread for each situation 1,2,3
#define MAX_THREADS 3

void* thread_routine(void*);
void  cleanup_routine(void*);

int main(int argc, char** argv)
{
	int err;
	long i;
	pthread_t thrds[MAX_THREADS];


	for(i=0; i < MAX_THREADS; ++i)
	{
		err = pthread_create(&thrds[i], NULL, thread_routine, (void*)i);
		if(err)
			err_abort(err, "pthread_create");

		printf("\nLaunched thread: %d", i);
	}

	sleep(1);
	printf("\nCANCELLING ...");

	for(i=0; i < MAX_THREADS; ++i)
	{
		err = pthread_cancel(thrds[i]);
		if(err)
			err_abort(err, "pthread_cancel");

		printf("\nCancel thread: %d", i);
	}


	printf("\nCHECKING STATUS ...");

	// look up exit status, should be PTHREAD_CANCELED
	for(i=0; i < MAX_THREADS; ++i)
	{
		void* retval;
		err = pthread_join(thrds[i], &retval);
		if(err)
			err_abort(err, "pthread_join");

		if(retval == PTHREAD_CANCELED)
			printf("\nThread: %d confimed CANCELING", i);
		else
			printf("\nThread: %d DIDN'T CANCELED", i);
	}


	printf("\nEXIT_SUCCESS :)\n");

	return EXIT_SUCCESS;
}

void* thread_routine(void* arg)
{
	long* ptr;
	ptr = malloc(sizeof(long));
	*ptr = (long) arg;

	pthread_cleanup_push(cleanup_routine, &ptr);

	printf("\n\tthread: %d working ...", *ptr);

	while(1)
	{
		wait(5);
	}

	pthread_cleanup_pop(1);
	return arg;
}

void cleanup_routine(void* arg)
{
	long** ptr = (long**)arg;

	printf("\n\tthread: %d cancelled, cleaning up ...", **ptr);
	free(*ptr);
	*ptr = 0;
}
