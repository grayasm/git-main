/*  The copyprivate clause can be used to broadcast values acquired by a
    single thread directly to all instances of the private variables in the
    other threads.

    The thread that executes the structured block associated with the single
    construct broadcasts the values of the private variables (e.g. i,j)
    from its implicit task's data environment to the data environments
    of the other implicit tasks in the thread team.

    The broadcast completes before any of the threads have left the barrier
    at the end of the construct.
*/


#include <stdio.h>
#include <omp.h>


int i,j;
#pragma omp threadprivate(i,j)

int main(int argc, char** argv)
{
	const int n = 8;
	int a[n][2] = {{1, -1}, {2, -2}, {3, -3}, {4, -4},
	               {5, -5}, {6, -6}, {7, -7}, {8, -8}};

#pragma omp parallel num_threads(n)
	{
#pragma omp single copyprivate(i,j)
		{
			int TID = omp_get_thread_num ();
			i = a[TID][0];
			j = a[TID][1] * 100;

			printf ("single thread= %d i= %d j= %d\n", TID, i,j);

		}/* end of single block (barrier) */

		printf ("thread= %d i= %d j= %d\n", omp_get_thread_num (), i,j);
	}/* end of parallel region */

	return 0;
}
