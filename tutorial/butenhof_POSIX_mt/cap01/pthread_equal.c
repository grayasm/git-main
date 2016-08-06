/*
 * pthread_equal - compare thread IDs
 *
 * man pthread_equal  (Linux Programmer's Manual)
 *
 * int pthread_equal(pthread_t t1, pthread_t t2); the function compares
 *     two thread identifiers. If the two thread IDs are equal
 *     pthread_equal() returns a nonzero value; otherwise it returns 0.
 *
 * The function always succeeds.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"

void* start_routine(void*);
#define MAX_THREADS 6
pthread_t thread[MAX_THREADS];

int main(int argc, char** argv)
{
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
    pthread_t thID = pthread_self();

	if((int)p >= 0)
	{
        sleep(rand()%3);

        printf("\n\tth: %d pthread_equal(%d) ret= %d",
               (int)p,
               (unsigned long)thID,
               pthread_equal(thread[(int)p], thID)
	        );

		pthread_exit(p);
	}

	return (void*)p;
}
