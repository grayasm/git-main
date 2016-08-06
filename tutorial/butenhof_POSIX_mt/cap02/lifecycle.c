#include <pthread.h>
#include "errors.h"

/* Thread start routine */
void* thread_routine(void* args)
{
	return args;
}

int main(int argc, char** argv)
{
	pthread_t thread_id;
	void* thread_result;
	int status;

	status = pthread_create(&thread_id, NULL, thread_routine, NULL);
	if(status != 0)
		err_abort(status, "Create thread");

	status = pthread_join(thread_id, &thread_result);
	if(status != 0)
		err_abort(status, "Join thread");

	if(thread_result == NULL)
	{
		printf("\nthread returned correct value: OK\n");
		return 0;
	}
	else
	{
		printf("\nthread returned incorrect value: NOT-OK\n");
		return 1;
	}
} // main
