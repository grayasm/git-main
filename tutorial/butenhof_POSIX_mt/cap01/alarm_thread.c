

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"


typedef struct alarm_tag
{
	int    seconds;
	char   message[64];
} alarm_t;

void* alarm_thread(void* arg)
{
	alarm_t*    alarm;
	int         status;
	pthread_t   self;

	alarm = (alarm_t*)arg;
	/* Detaches the calling thread. The function marks the given thread as detached.
	 * When a detached thread terminates, its resources are automatically released
	 * back to the system without the need for another thread to join with the
	 * terminated thread.
	 */
	// obtain the ID of the calling thread
	self = pthread_self();
	// detach a thread
	status = pthread_detach( self );

	if(status != 0)
		err_abort(status, "Detach thread");

	sleep(alarm->seconds);
	printf("(%d) %s\n", alarm->seconds, alarm->message);

	/* allocates the memory in one thread and releases it from another thread
	 */
	free(alarm);
	return NULL;
}



int main(int argc, char* argv[])
{
	int status;
	char line[128];
	alarm_t* alarm;
	pthread_t thread;


	while(1)
	{
		printf("Alarm> ");
		if(fgets(line, sizeof(line), stdin) == NULL) exit(0);
		if(strlen(line) <= 1) continue;
		alarm = (alarm_t*)malloc(sizeof(alarm_t));
		if(alarm == NULL)
			errno_abort("Allocate alarm");

		/*
		 * Parse input line into seconds (%d) and a message (%64[^\n]),
		 * consisting of up to 64 characters separated from the seconds by
		 * whitespace.
		 */
		if(sscanf(line, "%d %64[^\n]", &alarm->seconds, alarm->message) < 2)
		{
			fprintf(stderr, "Bad command\n");
			free(alarm);
		}
		else
		{
			status = pthread_create(
				&thread,
				NULL,
				alarm_thread,
				alarm);

			if(status != 0)
				err_abort(status, "Create alarm thread");
		}
	}
}; // main
