#include <pthread.h>
#include "errors.h"


static int counter;

/* Loop until canceled. The thread can be canceled only
 * when it calls pthread_testcancel, which it does each 1000
 * iterations.
 */
void* thread_routine(void* arg)
{
	DPRINTF(("thread_routine starting\n"));
	for(counter = 0; /*null*/ ; counter++)
	{
		if((counter % 10000) == 0)
		{
			DPRINTF(("calling testcance\n"));
			pthread_testcancel();
		}
	}
}


int main(int argc, char** argv)
{
	pthread_t thread_id;
	void* result;
	int status;

#ifdef sun
	/*
	 * On Solaris 2.5, threads are not timesliced. To ensure
	 * that our two threads can run concurrently, we need to
	 * increase the concurrency level to 2.
	 */
	DPRINTF(("Setting concurrency level to 2\n"));
	thr_setconcurrency(2);
#endif

	status = pthread_create(&thread_id,
	                        NULL,
	                        thread_routine,
	                        NULL);
	if(status) err_abort(status, "Create thread");
	sleep(2);

	DPRINTF(("calling cancel\n"));
	status = pthread_cancel(thread_id);
	if(status) err_abort(status, "cancel thread");

	DPRINTF(("calling join\n"));
	status = pthread_join(thread_id, &result);
	if(status) err_abort(status, "Join thread");

	if(result == PTHREAD_CANCELED)
		printf("Thread canceled at iteration %d\n", counter);
	else
		printf("Thread was not canceled\n");
	return 0;
}
