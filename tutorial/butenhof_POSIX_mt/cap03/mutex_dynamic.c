/*
 * Define a structure, with a mutex
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

typedef struct my_struct_tag
{
	pthread_mutex_t   mutex; /* Protects access to value */
	int               value; /* Access protected by mutex */
} my_struct_t;


int main(int argc, char** argv)
{
	my_struct_t*    data;
	int             status;

	data = malloc(sizeof(my_struct_t));
	if(data == NULL)
		errno_abort("Allocate structure");

	status = pthread_mutex_init(&data->mutex, NULL);
	if(status)
		err_abort(status, "Init mutex");

	status = pthread_mutex_destroy(&data->mutex);
	if(status != 0)
		err_abort(status, "Destroy mutex");


	free(data);

	printf("\nSUCCESS\n");
	return status;
}
