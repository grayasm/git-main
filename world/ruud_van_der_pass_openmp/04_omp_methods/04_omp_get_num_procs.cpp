/*  int omp_get_num_procs(void);

    Returns the number of processors online on that device.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char* argv[])
{
	printf ("num procs: %d\n", omp_get_num_procs ());

#pragma omp parallel
#pragma omp master
	{
		printf ("num procs: %d\n", omp_get_num_procs ());
	}/* end of parallel */

	return 0;
}

/*
$> ./04_omp_get_num_procs
num procs: 10
num procs: 10
*/
