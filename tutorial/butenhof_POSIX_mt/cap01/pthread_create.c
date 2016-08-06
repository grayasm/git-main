/*
 * pthread_create(pthread_t*, const pthread_attr_t*,
 *                void* (*start_routine)(void*), void* arg);
 *
 * man pthread_create  (Linux Programmer's Manual)
 *
 * pthread_create() function starts a new thread in the calling
 *                  process. The new thread starts execution
 *                  by invoking start_routine() with arg as sole
 *                  argument.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"

void* start_routine(void*);
#define MAX_THREADS 10

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

	sleep(8);

	printf("\nExit main thread\n\n");
	return 0;
}; // main



void* start_routine(void* p)
{
	sleep(rand()%5);
	printf("\n\tRunning thread %d", (int)p);
	return (void*)p;
}
