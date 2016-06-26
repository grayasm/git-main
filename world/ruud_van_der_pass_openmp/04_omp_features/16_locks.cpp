/* Synchrnization construct: locks

   syntax: void omp_"func"_lock (omp_lock_t *lck)

   func may assume the values: init, destroy, set, unset, test.

   In addition to the synchronization features introduced above, the OpenMP API
   provides a set of low-level, general-purpose locking runtime library routines
   , similar in function to the use of semaphores.
   These routines provide greater flexibility for synchronization than does the
   use of critical sections or atomic constructs.
*/

#include <stdio.h>
#include <omp.h>

#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32


int main(int argc, char** argv)
{
	setbuf (stdout, NULL); // flush stdout
	const int MAX=6;
	int i, a[MAX];

	omp_lock_t  mylock;
	omp_init_lock (&mylock);


#pragma omp parallel for shared(a) private(i)
	for (i=0; i<MAX; i++)
	{
		a[i] = omp_get_thread_num ();

		omp_set_lock (&mylock);
		printf ("locked   thread %d i= %d\n", a[i], i);
		sleep(1);
		printf ("unlocked thread %d\n", a[i]);
		omp_unset_lock (&mylock);

	}/* end of parallel region */


	omp_destroy_lock (&mylock);

	return 0;
}
