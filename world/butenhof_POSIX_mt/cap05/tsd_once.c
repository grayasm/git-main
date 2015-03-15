/*
 * Sample on using: pthread_key_create and accessing thread specific data,
 * from TSL thread specific storage.
 */

#include <pthread.h>
#include <limits.h>
#include "errors.h"



/* Structure used as the value for thread-specific data key. */
typedef struct tsd_tag
{
    pthread_t   thread_id;
    char*       string;
} tsd_t;

pthread_key_t tsd_key;      /* Thread-specific data key */
pthread_once_t key_once = PTHREAD_ONCE_INIT;

/* One time initialization routine used with the pthread_once
 * control block.
 */
void once_routine(void)
{
    int err;

    printf("initializing key\tmaximum supported by Pthreads: %d\n", PTHREAD_KEYS_MAX);
    err = pthread_key_create(&tsd_key, NULL);
    if (err) err_abort(err, "Create key");
}


/* Thread start routine that uses pthread_once to dynamically
 * create a thread specific data key.
 */
void* thread_routine(void* arg)
{
    tsd_t* value;
    int err;

    err = pthread_once(&key_once, once_routine);
    if (err) err_abort(err, "Once init");

    value = (tsd_t*) malloc(sizeof(tsd_t));
    if(value == NULL) errno_abort("Allocate key value");

    err = pthread_setspecific(tsd_key, value);
    if (err) err_abort(err, "Set tsd");

    printf("%s set tsd value %p\n", (char*)arg, (void*)value);

    value->thread_id = pthread_self();
    value->string = (char*) arg;
    value = (tsd_t*) pthread_getspecific(tsd_key);
    printf("%s starting ...\n", value->string);
    sleep(2);
    value = (tsd_t*)pthread_getspecific(tsd_key);
    printf("%s done ...\n", value->string);
    return NULL;
}

int main (int argc, char** argv)
{
    pthread_t thread1, thread2;
    int err;

    err = pthread_create(&thread1, NULL, thread_routine, "thread 1");
    if (err) err_abort(err, "Create thread 1");

    err = pthread_create(&thread2, NULL, thread_routine, "thread 2");
    if (err) err_abort(err, "Create thread 2");
    pthread_exit(NULL);

    return 0;
}
