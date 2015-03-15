/*
 * pthread_exit(void* retval);
 *
 * man pthread_exit  (Linux Programmer's Manual)
 *
 * pthread_exit(void* retval) fuction terminates the calling thread and returns
 * a value via retval that if the thread is joinable is available to another
 * thread in the same process that calls pthread_join(3).
 * This function does not return to the caller, and it always succeeds.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"

void* start_routine(void*);
#define MAX_THREADS 6

int main(int argc, char** argv)
{
	pthread_t thread;
	int error;
	int i;

	for(i=0; i < MAX_THREADS; ++i)
	{
		error = pthread_create(
			&thread,
			0,
			start_routine,
			(void*)i);

		if(error != 0)
			errno_abort("pthread_create");
		else
			printf("\nLaunched thread %d", i);
	}

	sleep(10);

	printf("\nExit main thread\n\n");
	return 0;
}; // main



void* start_routine(void* p)
{
	if((int)p >= 0)
	{
		sleep(rand()%5);
		printf("\n\tpthread_exit(%d)", (int)p);
		pthread_exit(p);
	}

	return (void*)p;
}
