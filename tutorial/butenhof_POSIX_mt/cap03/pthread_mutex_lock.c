/*
 * int pthread_mutex_lock(pthread_mutex_t* mutex)
 *
 *     A mutex object shall be locked by calling pthread_mutex_lock(). If the
 *     mutex is already locked the calling thread shall block until the mutex
 *     becomes available. The operation shall return with the mutex in the locked
 *     state.
 *
 *     For a mutex with type PTHREAD_MUTEX_NORMAL:
 *         - attempting to relock causes deadlock
 *         - attempting to unlock a mutex that the thread has not locked results
 *           in undefined behavior;
 *
 *     For a mutex with type PTHREAD_MUTEX_ERRORCHECK:
 *         - a thread attempting to relock a mutex that it has already locked an
 *           error shall be returned.
 *         - a thread attempting to unlock a mutex that it has not locked or
 *           which is unlocked an error shall be returned.
 *
 *     For a mutex with type PTHREAD_MUTEX_RECURSIVE:
 *         - the mutex shall maintain the concept of a lock count. Every time the
 *           thread relocks the mutex the lock count shall be incremented by one,
 *           and when unlocks it the count shall be decremented by one. When the
 *           lock count reaches zero, the mutex shall become available for other
 *           threads to aquire. If a thread attempts to unlock a mutex that it
 *           has not locked or to unlock a mutex that is unlocked an error shall
 *           be returned.
 *
 *     For a mutex with type PTHREAD_MUTEX_DEFAULT:
 *         - attempting to recursively lock the mutex results in undefined behavior
 *         - a thread attempting to unlock a mutex that it has not locked or it
 *           is already unlocked results in undefined behavior
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"


pthread_mutex_t gMutex;
pthread_mutexattr_t attr;

#define MAX_THREADS 3

void* start_routine(void*);


int main(int argc, char** argv)
{
	int err;
	long i;
	int type;
	pthread_t thrds[MAX_THREADS];

	// Pick a testing value for the mutex type.
    //type = PTHREAD_MUTEX_NORMAL;            (crashes on faults)
	//type = PTHREAD_MUTEX_ERRORCHECK;        (gives error on faults)
	type = PTHREAD_MUTEX_RECURSIVE;         //(allows multiple locks on Mutex)
	//type = PTHREAD_MUTEX_DEFAULT;           (crashes on faults)

	/* no error checking just to see it clearer
	 * for error checking do:
	 * if(err) err_abort(err, "pthread_mutex_ ...");
	 */
	pthread_mutexattr_init (&attr);
	pthread_mutexattr_settype (&attr, type);
	pthread_mutex_init(&gMutex, &attr);

	for(i=0; i < MAX_THREADS; ++i)
	{
		err = pthread_create(&thrds[i], NULL, start_routine, (void*)i);
		if(err)
			err_abort(err, "pthread_create");

		printf("\nLaunched thread %d", i);
	}


	for(i=0; i < MAX_THREADS; ++i)
	{
		void* retval;
		err = pthread_join(thrds[i], &retval);
		if(err)
			err_abort(err, "pthread_join");

		printf("\nThread %d returned %d", i, (long) retval);
	}

	/* clean up Mutex Attribute and Mutex resources
	 * no error checking atm
	 */
	pthread_mutex_destroy(&gMutex);
	pthread_mutexattr_destroy(&attr);


	printf("\nExit now ...\n");
	return EXIT_SUCCESS;
} // main


void* start_routine(void* arg)
{
	int err;
	long i;

	i = (long) arg;
	err = pthread_mutex_lock(&gMutex);
	if(err)
		err_abort(err, "pthread_mutex_lock");
	printf("\n\tMutex locked arg= %d", i);

	sleep(1);

	if(i)
	{
		long j = i-1;
		printf("\n\t\tRelock mutex arg= %d", j);

		// Attempting to relock the mutex can result in a crash,error,nothing
		// depending on mutex type
		start_routine((void*)j);
		printf("\n\t\tUnlock mutex arg= %d", j);
	}

	printf("\n\tMutex unlock arg= %d", i);
	err = pthread_mutex_unlock(&gMutex);
	if(err)
		err_abort(err, "pthread_mutex_unlock");

	return arg;
}
