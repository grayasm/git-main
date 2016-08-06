/* Example of use:
 *
 *         int pthread_condattr_init(pthread_condattr_t* attr);
 *         int pthread_condattr_destroy(pthread_condattr_t* attr);
 *
 * Destroy and initialize the condition variable attributes object.
 */

#include <pthread.h>
#include "errors.h"

pthread_cond_t  cond;

int main(int argc, char** argv)
{
	pthread_condattr_t  cond_attr;
	int status;

	status = pthread_condattr_init(&cond_attr);
	if(status) err_abort(status, "Create attr");
	printf("Initialized attributes");

#ifdef _POSIX_THREAD_PROCESS_SHARED
	status = pthread_condattr_setpshared(&cond_attr,
	                                     PTHREAD_PROCESS_PRIVATE);
	if(status) err_abort(status, "Set pshared.\n");
	printf("\nSet pshared");
#endif

	status = pthread_cond_init(&cond, &cond_attr);
	if(status) err_abort(status, "Init cond");
	printf("\nInitialized condition variable.\n");

	return 0;
}
