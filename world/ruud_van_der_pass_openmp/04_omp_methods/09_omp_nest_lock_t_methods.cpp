/*  void omp_init_nest_lock(omp_nest_lock_t *lock);
    void omp_set_nest_lock(omp_nest_lock_t *lock);
    int omp_test_nest_lock(omp_nest_lock_t *lock);
    void omp_unset_nest_lock(omp_nest_lock_t *lock);
    void omp_destroy_nest_lock(omp_nest_lock_t *);


    omp_init_nest_lock: Initialize a nested lock. After initialization, the lock
    is in an unlocked state and the nesting count is set
    to zero.

    omp_set_nest_lock: Before setting a nested lock, the lock variable must be
    initialized by omp_init_nest_lock. The calling thread is
    blocked until the lock is available. If the lock is
    already held by the current thread, the nesting count
    for the lock is incremented.

    omp_test_nest_lock: Before setting a nested lock, the lock variable must be
    initialized by omp_init_nest_lock. Contrary to
    omp_set_nest_lock, omp_test_nest_lock does not block if
    the lock is not available. If the lock is already held
    by the current thread, the new nesting count is returned.
    Otherwise, the return value equals zero.

    omp_unset_nest_lock: A nested lock about to be unset must have been locked
    by omp_set_nested_lock or omp_test_nested_lock before.
    In addition, the lock must be held by the thread
    calling omp_unset_nested_lock. If the nesting count
    drops to zero, the lock becomes unlocked. If one ore
    more threads attempted to set the lock before, one of
    them is chosen to, again, set the lock to itself.

    omp_destroy_nest_lock: Destroy a nested lock. In order to be destroyed, a
    nested lock must be in the unlocked state and its
    nesting count must equal zero.
*/

#include <stdio.h>
#include <omp.h>


omp_nest_lock_t  nestable_lock;

int main(int argc, char** argv)
{
    omp_init_nest_lock (&nestable_lock);

#pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num ();
        while (!omp_test_nest_lock (&nestable_lock))
            printf ("thread %d - failed to acquire lock\n", tid);

        printf ("\tthread %d - acquired lock\n", tid);
        if (omp_test_nest_lock (&nestable_lock))
        {
            printf ("\t\tthread %d - acquired lock again\n", tid);
            printf ("\t\tthread %d - released lock\n", tid);
            omp_unset_nest_lock (&nestable_lock);
        }

        printf ("\tthread %d - released lock\n", tid);
        omp_unset_nest_lock (&nestable_lock);
    }/* end of parallel */

    omp_destroy_nest_lock (&nestable_lock);

    return 0;
}
/*
./09_omp_nest_lock_t_methods
thread 1 - failed to acquire lock
thread 0 - failed to acquire lock
thread 2 - failed to acquire lock
thread 0 - failed to acquire lock
thread 2 - failed to acquire lock
	thread 3 - acquired lock
		thread 3 - acquired lock again
		thread 3 - released lock
	thread 3 - released lock
thread 1 - failed to acquire lock
	thread 1 - acquired lock
		thread 1 - acquired lock again
thread 0 - failed to acquire lock
thread 2 - failed to acquire lock
thread 2 - failed to acquire lock
thread 2 - failed to acquire lock
		thread 1 - released lock
	thread 1 - released lock
	thread 2 - acquired lock
		thread 2 - acquired lock again
		thread 2 - released lock
	thread 2 - released lock
thread 0 - failed to acquire lock
	thread 0 - acquired lock
		thread 0 - acquired lock again
		thread 0 - released lock
	thread 0 - released lock
*/
