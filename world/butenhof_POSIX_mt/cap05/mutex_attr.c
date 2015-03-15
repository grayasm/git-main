#include <pthread.h>
#include "errors.h"


pthread_mutex_t  mutex;

int main(int argc, char** argv)
{
	pthread_mutexattr_t mutex_attr;
	int status;

	status = pthread_mutexattr_init(&mutex_attr);
	if(status) err_abort(status, "Create attr");
	printf("\nInitialized mutex attributes.");

#ifdef _POSIX_THREAD_PROCESS_SHARED
	status = pthread_mutexattr_setpshared(
		&mutex_attr,
		PTHREAD_PROCESS_PRIVATE);

	if(status) err_abort(status, "Set pshared");

	printf("\nSet pshared.");
#endif

	status = pthread_mutex_init(&mutex, &mutex_attr);
	if(status) err_abort(status, "pthread_mutex_init(&mutex, &attr);");

	printf("\nMutex initialized.\n");
	return 0;
}
