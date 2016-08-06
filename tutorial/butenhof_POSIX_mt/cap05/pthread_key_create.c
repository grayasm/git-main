/*
 * 1) I allocate TLS via pthread_key_t tls_key variable.
 * 2) Creation of key is controlled by pthread_once_t  tls_once variable.
 * 3) I do not call pthread_key_delete. If I were to, I would have done it in
 *    the main thread, not in one of the threads because will kill it for other
 *    threads too.
 * 4) I do memory allocation in each thread. (malloc)
 * 5) Before exiting thread the memory is released. (free)
 */
#include <pthread.h>
#include "errors.h"

#define MAX_THREADS    6



/* Thread Local Storage control variable. It ensures that the TLS key is
 * created only once.
 */
static pthread_once_t tls_once = PTHREAD_ONCE_INIT;

/* Thread Local Storage variable. (key)*/
static pthread_key_t tls_key;


void initialize_tls_once(void)
{
	int err;

	printf("\n\tCreate TLS key once only!!");

	/* Create unique TLS key for all threads. */
	err = pthread_key_create(&tls_key, NULL);
	if(err) err_abort(err, "pthread_key_create");
}


void check_ptr(long thid)
{
	int err;
	long *ptr;

	/* Show TLS storage. */
	ptr = (long*)pthread_getspecific(tls_key);
	if(ptr == NULL) err_abort(err, "pthread_getspecific");

	printf("\n\tCheck memory: thread= %d  tls *ptr= %d", thid, (long)*ptr);
}


void *start_routine(void *arg)
{
	int err;
	long *ptr;

	/* TLS key initialization (once for ALL threads only). */
	err = pthread_once(&tls_once, initialize_tls_once);
	if(err) err_abort(err, "pthread_once");

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

	/* Dereference memory, different value in each thread. */
	check_ptr((long) arg);

	/* Release the memory and TLS. */
	ptr = (long*) pthread_getspecific(tls_key);
	if(ptr == NULL) err_abort(err, "pthread_getspecific");

	free(ptr);

	/* Any attempt to use key following the call  to  pthread_key_delete()
	 * results in undefined behavior.
	 *
	 * err = pthread_key_delete(tls_key);
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

	printf("\nExit OK.\n");
	return EXIT_SUCCESS;
}
