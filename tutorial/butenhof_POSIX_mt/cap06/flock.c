#include <pthread.h>
#include "errors.h"


/* This routine writes a prompt to stdout (passed as the thread's
 * "arg"), and reads a response. All other I/0 to stdin and stdout
 * is prevented by the file locks until both prompt and fgets are
 * complete.
 */
void *prompt_routine(void *arg)
{
	char *prompt = (char*)arg;
	char *string;
	int len;

	string = (char*) malloc (128);
	if (string == NULL) errno_abort ("Alloc string");

	flockfile (stdin);
	flockfile (stdout);

	printf (prompt);
	if (fgets (string, 128, stdin) == NULL)
		string[0] = '\0';
	else {
		len = strlen (string);
		if (len > 0 && string[len-1] == '\n')
			string[len-1] = '\0';
	}

	funlockfile (stdout);
	funlockfile (stdin);

	return (void*)string;
}


int main (int argc, char **argv)
{
	pthread_t  thread1, thread2, thread3;
	char *string;
	int err;


#ifdef sun
	/* On Solaris 2.5, threads are not timesliced. To ensure
	 * that our threads can run concurrently, we need to
	 * increase the concurrency level.
	 */
	DPRINTF (("Setting concurrency level to 4\n"));
	thr_setconcurrency (4);
#endif

	err = pthread_create (&thread1, NULL, prompt_routine, "Thread 1> ");
	if (err) err_abort (err, "Create thread 1");

	err = pthread_create (&thread2, NULL, prompt_routine, "Thread 2> ");
	if (err) err_abort (err, "Create thread 2");

	err = pthread_create (&thread3, NULL, prompt_routine, "Thread 3> ");
	if (err) err_abort (err, "Create thread 3");

	err = pthread_join (thread1, (void**)&string);
	if (err) err_abort (err, "Join thread 1");
	printf ("Thread 1: \"%s\"\n", string);
	free (string);

	err = pthread_join (thread2, (void**)&string);
	if (err) err_abort (err, "Join thread 2");
	printf ("Thread 2: \"%s\"\n", string);
	free (string);

	err = pthread_join (thread3, (void**)&string);
	if (err) err_abort (err, "Join thread 3");
	printf ("Thread 3: \"%s\"\n", string);
	free (string);

	return 0;
}
