/*  int omp_get_thread_num(void);

    Returns a unique thread identification number within the current team.
    In a sequential parts of the program, omp_get_thread_num always returns 0.
    In parallel regions the return value varies from 0 to omp_get_num_threads-1
    inclusive. The return value of the master thread of a team is always 0.
 */

#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{

#pragma omp parallel num_threads(4)
	{
		int tid = omp_get_thread_num ();
		printf ("thread %d\n", tid);
	}/* end of parallel region */

	return 0;
}

/*
$> ./03_omp_get_thread_num
thread 2
thread 3
thread 0
thread 1
*/
