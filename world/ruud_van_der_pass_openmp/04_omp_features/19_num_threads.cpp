/*  The num threads clause is supported on the parallel construct only and
    can be used to specify how many threads should be in the team executing
    the parallel region.

    syntax: num_threads(scalar-integer-expression )

    strangly enough num_threads(30) will parallelize with 30 threads although
    the cpu has only 4 or 8.
 */


#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
#pragma omp parallel
	{
		printf("1-parallel thread %d\n", omp_get_thread_num ());

	}/* end of parallel region */


#pragma omp parallel num_threads(4)
	{
		printf("2-parallel thread %d\n", omp_get_thread_num ());

	}/* end of parallel region */

	return 0;
}
