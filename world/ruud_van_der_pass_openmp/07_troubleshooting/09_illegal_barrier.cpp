/*  Cap7 pag 254, Fig. 7.12 Illegal use of the barrier.

    The barrier is not encountered by all threads in the team, and therefore
    this is an illegal OpenMP program. The runtime behavior is undefined.
*/


#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{

#pragma omp parallel // Incorrect use of the barrier
	{
		if (omp_get_thread_num () == 0)
		{
			// ...
			printf ("barrier A in thread=%d\n", omp_get_thread_num ());
#pragma omp barrier

		}
		else
		{
			// ...
			printf ("barrier B in thread=%d\n", omp_get_thread_num ());
#pragma omp barrier

		}
	}/* end of parallel */

	return 0;
}
