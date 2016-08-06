/*
 * pthread_cancel(pthread_t thread);
 *
 * man pthread_cancel  (Linux Programmer's Manual)
 *
 * pthread_cancel() -send a cancellation request to the thread "thread". Whether
 *                   and when the target reacts to the cancellation request
 *                   depends on two attributes that are under the control of that
 *                   thread: its cancelability state and type.
 *                   A thread's cancelability state, determined by
 *                   pthread_setcancelstate(3) can be enabled (the default for
 *                   new threads) or disabled.
 *                   A cancelation request remains queued until the thread
 *                   enables cancellation (if previously disabled).
 *                   If a thread has enabled cancellation, then its cancelability 
 *                   type determines when cancellation occurs:
 *                   pthread_setcanceltype(3)
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

	sleep(1);
	printf("\nCancel ALL threads");

	for(i=0; i < MAX_THREADS; ++i)
	{
		error = pthread_cancel(thread[i]);
		if(error != 0)
			errno_abort("pthread_cancel");
		else
			printf("\nCancel thread= %d", i);
	}

	printf("\nCheck running threads");

	for(i=0; i < MAX_THREADS; ++i)
	{
		void* retval;
		int error;

		error = pthread_join(thread[i], &retval);

		if(error != 0)
			errno_abort("pthread_join");
		else if(retval == PTHREAD_CANCELED)
			printf("\nThread %d CANCELED", i);
		else
			printf("\nThread %d NOT CANCELLED, returned= %d", i, (int)retval);
	}

	printf("\nExit main thread\n\n");
	return 0;
}; // main



void* start_routine(void* p)
{
	if((int)p >= 0)
	{
		int s;
		/* disable cancellation for a while, so that we don't immediately
		   react to a cancellation request */
		s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		if(s != 0)
			errno_abort("pthread_setcancelstate");

		printf("\n\tcancellation disabled th: %d", (int)p);
		sleep(rand()%3);
		printf("\n\tcancellation enabled  th: %d", (int)p);
		s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		if(s != 0)
			errno_abort("pthread_setcancelstate");
		/* sleep is a cancellation point */
		sleep(5);

		/* should never get here */
		printf("\n\tSHOULD NEVER pthread_exit(%d)", (int)p);
		pthread_exit(p);
	}

	return (void*)p;
}
