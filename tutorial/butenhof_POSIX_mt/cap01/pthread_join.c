/*
 * pthread_join(pthread_t thread, void** retval);
 *
 * man pthread_join  (Linux Programmer's Manual)
 *
 * pthread_join()  waits for the thread specified by thread to terminate.
 *                 If that thread has already terminated, then pthread_join()
 *                 returns immediately. The thread specified by thread must
 *                 be joinable.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"

void* start_routine(void*);
#define MAX_THREADS 6

int main(int argc, char** argv)
{
	pthread_t thread[MAX_THREADS];
	int error;
	int i;

	for(i=0; i < MAX_THREADS; ++i)
	{
		error = pthread_create(
			&thread[i],
			0,
			start_routine,
			(void*)i);

		if(error != 0)
			errno_abort("pthread_create");
		else
			printf("\nLaunched thread %d", i);
	}

	printf("\nWait for all threads");
	printf("\nNOT OK to wait in order of threads creation");
	printf("\nPreferably to wait for ALL at once");

	for(i=0; i < MAX_THREADS; ++i)
	{
		void* retval;
		int error;

		error = pthread_join(thread[i], &retval);

		if(error != 0)
			errno_abort("pthread_join");
		else
			printf("\nThread %d retval= %d", i, (int)retval);
	}

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
