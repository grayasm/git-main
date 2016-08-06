/*
 * pthread_self - obtain ID of the calling thread
 *
 * man pthread_self  (Linux Programmer's Manual)
 *
 * pthread_t pthread_self(); function returns the ID of the calling thread. This
 *                           is the same value returned in *thread by pthread_create
 *                           call that created this thread.
 * This function always succeeds, returning the calling thread's ID.
 * To compare the pthread_t ID one must use pthread_equal(3) function.
 *
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
        printf("\n\tth: %d pthread_self ret= %d",(int)p,  (unsigned long)thID);
		pthread_exit(p);
	}

	return (void*)p;
}
