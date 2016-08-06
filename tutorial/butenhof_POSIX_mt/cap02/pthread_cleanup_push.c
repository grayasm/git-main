/*
 * pthread_cleanup_push - push and pop thread cancellation clean-up handlers
 *
 * void pthread_cleanup_push(void (*routine)(void*), void* arg);
 * void pthread_cleanup_pop(int execute);
 *
 *
 */

#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void* thread_routine(void*);
static void  cleanup_handler(void*);

#define handle_error_en(en, msg)     \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while(0)

static int done = 0;
static int cleanup_pop_arg = 0;
static int cnt = 0;


int main(int argc, char** argv)
{
	pthread_t thr;
	int s;
	void* res;

	s = pthread_create(&thr, NULL, thread_routine, NULL);
	if(s != 0)
		handle_error_en(s, "pthread_create");

	sleep(2); /* Allow new thread to run for a while */

	if(argc > 1)
	{
		if(argc > 2)
			cleanup_pop_arg = atoi(argv[2]);
		done = 1;
	}
	else
	{
		printf("canceling thread\n");
		s = pthread_cancel(thr);
		if(s != 0)
			handle_error_en(s, "pthread_cancel");
	}

	s = pthread_join(thr, &res);
	if(s != 0)
		handle_error_en(s, "pthread_join");

	if(res == PTHREAD_CANCELED)
		printf("thread was canceled; cnt = %d\n", cnt);
	else
		printf("thread terminated normally; cnt = %d\n", cnt);
	exit(EXIT_SUCCESS);

} // main


static void* thread_routine(void* arg)
{
	time_t start, curr;

	printf("new thread started\n");
	pthread_cleanup_push(cleanup_handler, NULL);
	curr = start = time(NULL);

	while(!done)
	{
		pthread_testcancel(); /* a cancellation point */

		if(curr < time(NULL))
		{
			curr = time(NULL);
			printf("cnt = %d\n", cnt); /* a cancellation point */
			cnt++;
		}
	}

	pthread_cleanup_pop(cleanup_pop_arg);
	return NULL;
}


static void cleanup_handler(void* arg)
{
	printf("called clean-up handler\n");
	cnt = 0;
}
