/*  void omp_init_lock(omp_lock_t *lock);
    void omp_set_lock(omp_lock_t *lock);
    int omp_test_lock(omp_lock_t *lock);
    void omp_unset_lock(omp_lock_t *lock);
    void omp_destroy_lock(omp_lock_t *lock);

    omp_init_lock: Initialize a simple lock. After initialization, the lock is
                   in an unlocked state.

    omp_set_lock:  Before setting a simple lock, the lock variable must be
                   initialized by omp_init_lock. The calling thread is blocked
                   until the lock is available. If the lock is already held by
                   the current thread, a deadlock occurs.

    omp_test_lock: Before setting a simple lock, the lock variable must be
                   initialized by omp_init_lock. Contrary to omp_set_lock,
                   omp_test_lock does not block if the lock is not available.
                   This function returns true upon success, false otherwise.
                   Here, true and false represent their language-specific
                   counterparts.

    omp_unset_lock: A simple lock about to be unset must have been locked by
                    omp_set_lock or omp_test_lock before. In addition, the lock
                    must be held by the thread calling omp_unset_lock. Then,
                    the lock becomes unlocked. If one or more threads attempted
                    to set the lock before, one of them is chosen to, again,
                    set the lock to itself.

    omp_destroy_lock: Destroy a simple lock. In order to be destroyed, a simple
                      lock must be in the unlocked state.

*/

#include <stdio.h>
#include <omp.h>


omp_lock_t lock;

int main(int argc, char** argv)
{
	omp_init_lock (&lock);

#pragma omp parallel num_threads(4)
	{
		int tid = omp_get_thread_num ();

		while (!omp_test_lock (&lock))
			printf ("thread %d - failed to aquire lock\n", tid);

		printf ("\tthread %d - aquired lock\n", tid);

		printf ("\tthread %d - released lock\n", tid);
		omp_unset_lock (&lock);
	}/* end of parallel */


	omp_destroy_lock (&lock);

	return 0;
}

/*
$> ./08_omp_lock_t_methods
	thread 0 - aquired lock
	thread 0 - released lock
thread 3 - failed to aquire lock
	thread 3 - aquired lock
	thread 3 - released lock
thread 1 - failed to aquire lock
	thread 1 - aquired lock
	thread 1 - released lock
thread 2 - failed to aquire lock
	thread 2 - aquired lock
	thread 2 - released lock
*/
