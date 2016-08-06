/*  Return the maximum number of threads used for the current parallel region
    that does not use the clause num_threads.

    syntax: int omp_get_max_threads(void);
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	omp_set_num_threads (8);
	printf ("main: %d\n", omp_get_max_threads ());

#pragma omp parallel
#pragma omp master
	{
		printf ("master: %d\n", omp_get_max_threads ());
	}/* end of parallel region */

	printf ("main: %d\n", omp_get_max_threads ());


#pragma omp parallel num_threads(3)
#pragma omp master
	{
		printf ("master: %d\n", omp_get_max_threads ());
	}/* end of parallel region*/


	printf ("main: %d\n", omp_get_max_threads ());

	return 0;
}

/*
$> ./02_omp_get_max_threads
main: 8
master: 8
main: 8
master: 8
main: 8
*/
