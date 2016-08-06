/*
 * 1) Create TLS key (pthread_key_t    tls_key) in the main thread, 1 time
 *    before all threads are created.
 * 2) Destroy TLS key also in the main thread at the end. This function
 *    pthread_key_delete cannot be really called in the thread function because
 *    it may kill the key for active threads using it.
 * 3) Memory attached to the key is allocated in the thread function and is
 *    released in the destructor function passed in pthread_key_create.
 */
#include <pthread.h>
#include "errors.h"

#define MAX_THREADS    4


/* Thread Local Storage variable. (key)*/
static pthread_key_t tls_key;


void check_ptr(long thid)
{
	int err;
	long *ptr;

	/* Show TLS storage. */
	ptr = (long*)pthread_getspecific(tls_key);
	if(ptr == NULL) err_abort(err, "pthread_getspecific");

	printf("\n\tCheck memory: thread= %d  tls *ptr= %d", thid, (long)*ptr);
}

void destructor(void *ptr)
{
	/* We release the memory allocated in each thread.
	 * This function called automatically by pthread framework.
	 * See pthread_key_create.
	 */
	long *mem = (long*)ptr;
	if(ptr)
	{
		printf("\n\tdestructor in thread %d", *mem);
		free(mem);
	}
}

void *start_routine(void *arg)
{
	int err;
	long *ptr;


	/* TLS storage - memory allocation per each thread. */
	ptr = (long*) pthread_getspecific(tls_key);
	if(ptr == NULL)
	{
		ptr = (long*) malloc(sizeof(long));
		if(ptr == NULL) errno_abort("malloc");

		*ptr = (long)arg;
		err = pthread_setspecific(tls_key, (void*) ptr);
		if(err) err_abort(err, "pthread_setspecific");
	}

	/* Check on the memory which has different address in each thread. */
	check_ptr((long) arg);

	/* Releasing the memory has been moved to the destructor function,
	 * from here.
	 *
	 *    ptr = (long*) pthread_getspecific(tls_key);
	 *    if(ptr == NULL) err_abort(err, "pthread_getspecific");
	 *    free(ptr);
	 */


	/* Return from the thread function. */
	pthread_exit(arg);
}


int main(int argc, char** argv)
{
	int err;
	long i;
	void* retval;
	pthread_t thrds[MAX_THREADS];


    /* Create unique TLS key for all threads,
     * this time passing a destructor to free the memory allocated by
     * each thread.
     */
	err = pthread_key_create(&tls_key, destructor);
	if(err) err_abort(err, "pthread_key_create");
	printf("\nCreated TLS key.");


	for(i = 0; i < MAX_THREADS; ++i)
	{
		err = pthread_create(&thrds[i], NULL, start_routine, (void*)i);
		if(err) err_abort(err, "create thread");
		printf("\nCreated thread %d", i);
	}

	for(i = 0; i < MAX_THREADS; ++i)
	{
		err = pthread_join(thrds[i], &retval);
		if(err) err_abort(err, "join thread");
		printf("\nThread %d returned %d", i, (long)retval);
	}



	/* Since TLS key will not be accessed by any thread anymore, we can
	 * delete it safely now.
	 */
	err = pthread_key_delete(tls_key);
	if(err) err_abort(err, "pthread_key_delete");

	printf("\nDeleted TLS key.");

	printf("\nExit OK.\n");
	return EXIT_SUCCESS;
}
