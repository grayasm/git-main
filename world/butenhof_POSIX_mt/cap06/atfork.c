#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>
#include "errors.h"


pthread_mutex_t    mutex = PTHREAD_MUTEX_INITIALIZER;
pid_t              self_pid;    /* pid of current process */



/* This routine will be called prior to executing the fork,
 * within the parent process.
 */
void fork_prepare(void)
{
	int err;

	/* Lock the mutex in the parent before creating the child,
	 * to ensure that no other thread can lock it (or change any
	 * associated shared state) until after the fork completes.
	 */
	err = pthread_mutex_lock(&mutex);
	if(err) err_abort(err, "Lock in prepare handler");
}


/* This routine will be called after executing the fork, within
 * the parent process.
 */
void fork_parent(void)
{
	int err;

	/* Unlock the mutex in the parent after the child has been
	 * created.
	 */
	err = pthread_mutex_unlock(&mutex);
	if(err) err_abort(err, "Unlock in parent handler");
}


/* This routine will be called after executing the fork, within
 * the child process.
 */
void fork_child(void)
{
	int err;

	/* Update the file scope "self_pid" within the child process, and
	 * unlock the mutex.
	 */
	self_pid = getpid();
	err = pthread_mutex_unlock(&mutex);
	if(err) err_abort(err, "Unlock in child handler");
}



/* Thread start routine, which will fork a new child process. */
void *thread_routine(void *arg)
{
	pid_t  child_pid;
	int    err;

	child_pid = fork();
	if(child_pid == (pid_t)-1) errno_abort("Fork");

	/* Lock the mutex -- without the atfork handlers, the mutex will
	 * remain locked in the child process and this lock attempt will
	 * hang (or fail with EDEADLK) in the child.
	 */
	err = pthread_mutex_lock (&mutex);
	if (err) err_abort (err, "Lock in child");

	err = pthread_mutex_unlock (&mutex);
	if (err) err_abort (err, "Unlock in child");

	printf ("After fork: %d (%d)\n", child_pid, self_pid);
	if(child_pid) {
		if ((pid_t)-1 == waitpid (child_pid, (int*)0, 0))
			errno_abort ("Wait for child");
	}
	return NULL;
}


int main (int argc, char** argv)
{
	pthread_t  fork_thread;
	int        atfork_flag = 1;
	int        err;

	if (argc > 1)
		atfork_flag = atoi (argv[1]);

	if (atfork_flag) {
		err = pthread_atfork (fork_prepare, fork_parent, fork_child);
		if (err) err_abort(err, "Register fork handlers");
	}

	self_pid = getpid ();
	err = pthread_mutex_lock (&mutex);
	if (err) err_abort (err, "Lock mutex");

	/* Create a thread while the mutex is locked. It will fork a
	 * process, which (without atfork handlers) will run with the
	 * mutex locked.
	 */
	err = pthread_create (&fork_thread, NULL, thread_routine, NULL);
	if (err) err_abort (err, "Create thread");

	sleep(5);

	err = pthread_mutex_unlock (&mutex);
	if (err) err_abort (err, "Unlock mutex");

	err = pthread_join (fork_thread, NULL);
	if (err) err_abort (err, "Join thread");

	return EXIT_SUCCESS;
}
