/*
 * C library routines: getc,putc,getchar,putchar uses a mutex to lock
 *           stdio file stream. The overhead of locking and unlocking the
 *           mutexes exceed the time of the character copy.
 *           Pthreads adds new functions that are fast because they do not
 *           perform any locking:
 *
 *    int getc_unlocked (FILE* stream)
 *    int getchar_unlocked (void)
 *    int putc_unlocked (int c, FILE* stream)
 *    int putchar_unlocked (int c)
 */

#include <pthread.h>
#include "errors.h"

/* This function writes a string (the function's arg) to stdout,
 * by locking the file stream and using putchar_unlocked to write
 * each character individually.
 */
void *lock_routine (void *arg)
{
	char *ptr;
	
	flockfile(stdout);
	for (ptr = arg; *ptr != '\0'; ptr++)
	{
		putchar_unlocked(*ptr);		
	}
	sleep(1);
	funlockfile(stdout);
	return NULL;
}


/* This function writes a string (the function's arg) to stdout,
 * by using putchar to write each character individually.
 * Although the internal locking of putchar prevents file stream
 * corruption, the writes of various threads may be interleaved.
 */
void *unlock_routine(void *arg)
{
	char *ptr;
	
	for(ptr = arg; *ptr != '\0'; ptr++)
	{
		putchar(*ptr);
	}
	sleep(1);
	return NULL;
}


int main(int argc, char** argv)
{
	pthread_t th1, th2, th3;
	int flock_flag = 1;
	void *(*thread_func)(void*);
	int status;
	
	if(argc > 1)
		flock_flag = atoi(argv[1]);
	if(flock_flag)
		thread_func = lock_routine;
	else
		thread_func = unlock_routine;
	
	status = pthread_create(&th1, NULL, thread_func, "this is thread 1\n");
	if(status) err_abort(status, "Create thread");
	
	status = pthread_create(&th2, NULL, thread_func, "this is thread 2\n");
	if(status) err_abort(status, "Create thread");
	
	status = pthread_create(&th3, NULL, thread_func, "this is thread 3\n");
	if(status) err_abort(status, "Create thread");
	
	pthread_exit(NULL);
}

























