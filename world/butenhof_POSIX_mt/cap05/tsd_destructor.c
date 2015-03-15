#include <pthread.h>
#include "errors.h"

/* Structure used as value of thread-specific data key. */
typedef struct private_tag
{
	pthread_t    thread_id;
	char         *string;
} private_t;


pthread_key_t   identity_key;        /* Thread specific data key */
pthread_mutex_t identity_key_mutex = PTHREAD_MUTEX_INITIALIZER;
long            identity_key_counter;


/* This routine is called as each thread terminates whith a value
 * for the thread specific data key. It keeps track of how many
 * threads still have values, and deletes the key when there are
 * no more references.
 */
void identity_key_destructor(void* value)
{
	private_t* private = (private_t*) value;
	int err;

	printf("thread \"%s\" exiting ...\n", private->string);
	free(value);

	err = pthread_mutex_lock(&identity_key_mutex);
	if(err) err_abort(err, "Lock mutex key");

	identity_key_counter--;
	if(identity_key_counter <= 0)
	{
		err = pthread_key_delete(identity_key);
		if(err) err_abort(err, "Delete key");
		printf("key deleted...\n");
	}

	err = pthread_mutex_unlock(&identity_key_mutex);
	if(err) err_abort(err, "Unlock key mutex");
}


/* Helper routine to allocate a new value for thread-specific
 * data key if the thread doesn't already have one.
 */
void* identity_key_get(void)
{
	void* value;
	int err;

	value = pthread_getspecific(identity_key);
	if(value == NULL)
	{
		value = malloc(sizeof(private_t));
		if(value == NULL) errno_abort("Allocate key value");

		err = pthread_setspecific(identity_key, (void*)value);
		if(err) err_abort(err, "Set TSD");
	}
	return value;
}


/* Thread start routine to use thread-specific data. */
void* thread_routine(void* arg)
{
	private_t *value;

	value = (private_t*)identity_key_get();
	value->thread_id = pthread_self();
	value->string = (char*) arg;
	printf("thread \"%s\" starting ...\n", value->string);
	sleep(2);
	return NULL;
}



int main(int argc, char** argv)
{
	pthread_t  thread_1, thread_2;
	private_t* value;
	int err;

	/* Create the TSD key, and set the reference counter to
	 * the number of threads that will use it (two thread_routine
	 * threads plus main). This must be done before creating
	 * the threads! Otherwise, if one thread runs the key's
	 * destructor before any other thread uses the key, it will
	 * be deleted.
	 *
	 * Note that there's rarely any good reason to delete a
	 * thread-specific data key.
	 */
	err = pthread_key_create(&identity_key, identity_key_destructor);
	if(err) err_abort(err, "Create key");

	identity_key_counter = 3;
	value = (private_t*) identity_key_get();
	value->thread_id = pthread_self();
	value->string = "Main thread";
	err = pthread_create(&thread_1, NULL, thread_routine, "Thread 1");
	if(err) err_abort(err, "Create thread 1");

	err = pthread_create(&thread_2, NULL, thread_routine, "Thread 2");
	if(err) err_abort(err, "Create thread 2");
	pthread_exit(NULL);
}
