/*
 * int  pthread_mutexattr_init (pthread_mutexattr_t*  attr);
 *
 *      Function shall initialize a mutex attributes object attr with the
 *      default value for all of the attributes defined by the implementation.
 *
 *      After a mutex attributes object has been used to initialize one or more
 *      mutexes, any function affecting the attributes object (including
 *      destruction) shall not affect any previously initialized mutexes.
 *
 *      On success function shall return zero; otherwise an error number.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

pthread_mutex_t mutex;


int main(int argc, char** argv)
{
	int err;
	pthread_mutexattr_t mtxattr;


	// Initialize the mutex's attributes with default settings.
	err = pthread_mutexattr_init(&mtxattr);
	if(err)
		err_abort(err, "pthread_mutexattr_init");

	// normal use of mutex: lock,trylock,timedlock,unlock
	pthread_mutex_init(&mutex, &mtxattr);
	pthread_mutex_lock(&mutex);
	printf("main thread locked a mutex");
	sleep(1);
	printf("\nmain thread about to release the mutex");
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	// Mutex's attributes must be released.
	err = pthread_mutexattr_destroy(&mtxattr);
	if(err)
		err_abort(err, "pthread_mutexattr_destroy");

	printf("\nmain thread exiting\n");
	return EXIT_SUCCESS;
}
