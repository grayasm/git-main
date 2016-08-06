/*
 * int pthread_detach(pthread_t thread);
 *
 * man pthread_detach  (Linux Programmer's Manual)
 *
 * pthread_detach() function marks the thread identified by 'thread' as detached.
 * When a detached thread terminates its resources are automatically released back
 * to the system without the need for another thread to join with the terminated
 * thread.
 * On success it returns zero. On error it returns an error number.
 * Once a thread has been detached, it can't be joined with pthread_join(3) or be
 * made joinable again.
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
	sleep(5);
	// cannot join a detached thread : undefined behavior or process is terminated
	// and we get a core dump

	printf("\nExit main thread\n\n");
	return 0;
}; // main



void* start_routine(void* p)
{
	sleep(rand()%3);
	printf("\n\tpthread_detach th: %d", (int)p);
	pthread_detach(pthread_self());
	return p;
}
