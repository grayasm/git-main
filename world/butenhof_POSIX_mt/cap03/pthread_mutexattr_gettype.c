/*
 * int pthread_mutexattr_gettype(const pthread_mutexattr_t* attr, int* type);
 *
 *     Get the mutex type attribute.
 *
 *     Valid mutex types include:
 * PTHREAD_MUTEX_NORMAL  - it does not detect deadlock (double locking).
 *         Unlocking a mutex locked by another thread-> undefined behavior.
 *         Unlocking an unlocked mutex-> undefined behavior.
 *
 * PTHREAD_MUTEX_ERRORCHECK - provides error checking and for invalid actions
 *         like the above an error code shall be returned.
 *
 * PTHREAD_MUTEX_RECURSIVE - a thread can relock a mutex it has locked before.
 *         Each lock will increment a counter and unlocking the mutex shall
 *         decrement it. When the counter is zero the mutex is unlocked.
 *         For any invalid action an error should be provided.
 *
 * PTHREAD_MUTEX_DEFAULT - any invalid action will result in invalid behavior.
 *
 *      In this sample we try to double lock a mutex which should result in
 *      an error inside the start_routine (thread function).
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"



void* start_routine(void* arg)
{
	int err;
	pthread_mutex_t* mutex = arg;


	printf("\n\tLock mutex once");
	err = pthread_mutex_lock(mutex);
	if(err) err_abort(err, "pthread_mutex_lock");

	printf("\n\tMutex locked");
	printf("\n\tLock mutex twice");
	sleep(1);

	// we should get an error on 2nd lock attempt.
	err = pthread_mutex_lock(mutex);
	if(err) err_abort(err, "pthread_mutex_lock");

	printf("\n\tShould NEVER get here");
	return arg;
}

int main(int argc, char** argv)
{
	int err;
	void* retval;
	int attr_type;
	pthread_t thread;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mtxattr;

	err = pthread_mutexattr_init(&mtxattr);
	if(err) err_abort(err, "pthread_mutexattr_init");

	err = pthread_mutexattr_settype(&mtxattr, PTHREAD_MUTEX_ERRORCHECK);
	if(err) err_abort(err, "pthread_mutexattr_settype");

	err = pthread_mutex_init(&mutex, &mtxattr);
	if(err) err_abort(err, "pthread_mutex_init\n");

	pthread_mutexattr_gettype(&mtxattr, &attr_type);
	if(attr_type != PTHREAD_MUTEX_ERRORCHECK)
	{
		printf("\nmutex attribute doesn't match\nabort()");
		abort();
	}

	pthread_create(&thread,
	               NULL,
	               start_routine,
	               (void*)&mutex);


	pthread_join(thread, &retval);
	pthread_mutex_destroy(&mutex);
	pthread_mutexattr_destroy(&mtxattr);

	return EXIT_SUCCESS;
} // main
