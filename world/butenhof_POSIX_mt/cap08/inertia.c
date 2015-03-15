#include <pthread.h>
#include "errors.h"

void *printer_thread (void *arg)
{
	char *string = *(char**)arg;

	printf ("%s\n", string);
	return NULL;
}


int main (int argc, char *argv[])
{
	pthread_t  printer_id;
	char *string_ptr;
	int i, status;

	string_ptr = "Before value";
	status = pthread_create (&printer_id,
							 NULL,
							 printer_thread,
							 (void*)&string_ptr);
	if (status != 0)
		err_abort (status, "Create thread");

	/*
	 * Give the thread a chance to get started if it's going to run
	 * in parallel, but not enough that the current thread is likely
	 * to be timesliced. (This is a tricky balance, and the loop may
	 * need to be adjusted on your system before you can see the bug.)
	 */
	for (i = 0; i < 10000000; i++);

	string_ptr = "After value";
	status = pthread_join (printer_id, NULL);
	if (status != 0)
		err_abort (status, "Join thread");
	return 0;
}
