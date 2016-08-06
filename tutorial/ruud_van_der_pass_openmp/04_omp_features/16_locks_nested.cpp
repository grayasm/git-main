/* Synchrnization construct: locks

   syntax: void omp_"func"_nest_lock (omp_nest_lock_t *lck)

   func may assume the values: init, destroy, set, unset, test.

   Locks are a set of low-level, general-purpose locking runtime library
   routines, similar in function to the use of semaphores.
   These routines provide greater flexibility for synchronization than does the
   use of critical sections or atomic constructs.

   nested locks can be locked multiple times from the same thread.
*/

#include <stdio.h>
#include <omp.h>

#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32


omp_nest_lock_t  mylock;

void func_relock();

int main(int argc, char** argv)
{
	setbuf (stdout, NULL); // flush stdout
	const int MAX=6;
	int i, a[MAX];

	omp_init_nest_lock (&mylock);


#pragma omp parallel for shared(a) private(i)
	for (i=0; i<MAX; i++)
	{
		a[i] = omp_get_thread_num ();

		omp_set_nest_lock (&mylock);
		printf ("locked   thread %d i= %d\n", a[i], i);

		func_relock ();

		printf ("unlocked thread %d\n", a[i]);
		omp_unset_nest_lock (&mylock);

	}/* end of parallel region */


	omp_destroy_nest_lock (&mylock);

	return 0;
}

void func_relock()
{
	omp_set_nest_lock (&mylock);
	printf ("relock   thread %d\n", omp_get_thread_num ());
	sleep(1);
	printf ("unlock\n");
	omp_unset_nest_lock (&mylock);
}
