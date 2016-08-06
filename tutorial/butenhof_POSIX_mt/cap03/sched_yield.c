/*
 * #include <sched.h>
 * int sched_yield(void);
 *
 *     Function shall force the running thread to relinquish the processor until
 *     it again becomes the head of its thread list. It takes no arguments.
 *
 *     Function shall return 0  if it completes successfuly; otherwise, it shall
 *     return a value of -1 and set errno to indicate the error.
 */

#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include "errors.h"


#define LOOPCONSTANT 1000
#define THREADS      3


pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
int              i,j,k,l;


void* start_routine(void* arg)
{
	int loop = 0;
	int localProcessingCompleted = 0;
	int numberOfLocalProcessingBursts = 0;
	int processingCompletedThisBurst = 0;
	int rc;

	printf("Entered secondary thread\n");
	for(loop = 0; loop < LOOPCONSTANT; ++loop)
	{
		rc = pthread_mutex_lock(&mutex);
		if(rc) err_abort(rc, "pthread_mutex_lock");

		/* Perform some not so important processing */
		i++, j++, k++, l++;

		rc = pthread_mutex_unlock(&mutex);
		if(rc) err_abort(rc, "pthread_mutex_unlock");

		/* Next part is not too important. Also, we just released a lock
		 * and would like to ensure that other threads get a chance in
		 * a more co-operative manner. This is an admittedly contrived
		 * example with no real purpose for doing sched_yield().
		 */
		sched_yield();
	}
	printf("Finished secondary thread\n");
	return NULL;
}


int main(int argc, char** argv)
{
	pthread_t    threadid[THREADS];
	int          rc = 0;
	int          loop = 0;

	printf("Enter testcase - %s\n", argv[0]);

	rc = pthread_mutex_lock(&mutex);
	if(rc) err_abort(rc, "pthread_mutex_lock");

	printf("Creating %d threads\n", THREADS);
	for(loop = 0; loop < THREADS; ++loop)
	{
		rc = pthread_create(&threadid[loop], NULL, start_routine, NULL);
		if(rc) err_abort(rc, "pthread_create");
	}

	sleep(1);
	rc = pthread_mutex_unlock(&mutex);
	if(rc) err_abort(rc, "pthread_mutex_unlock");

	printf("Wait for results\n");
	for(loop = 0; loop < THREADS; ++loop)
	{
		rc = pthread_join(threadid[loop], NULL);
		if(rc) err_abort(rc, "pthread_join");
	}

	pthread_mutex_destroy(&mutex);

	printf("Main completed\n");
	return EXIT_SUCCESS;
}
