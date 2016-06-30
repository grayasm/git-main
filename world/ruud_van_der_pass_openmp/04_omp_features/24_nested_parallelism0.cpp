/*  If a thread in a team executing a parallel region encounters another
    parallel construct, it creates a new team and becomes the master of that
    new team. This is generally referred to in OpenMP as “nested parallelism.”

    This API feature is implementation defined, thus Solaris or some other BSD
    is free to not provide parallelism. It means the nested parallel region
    will be inactive/ignored/serialized/executed by a single thread.

    nested parallelism controlled from terminal:

    $> export OMP_NESTED=TRUE
    $> ./24_nested_parallelism0

 */

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	printf ("Nested parallelism is %s\n",
	        omp_get_nested () == true ? "supported" : "not supported");


#pragma omp parallel
	{
		printf ("thread %d - outer parallel region\n", omp_get_thread_num ());

#pragma omp parallel num_threads(2)
		{
			printf ("\tTID %d - inner parallel region\n", omp_get_thread_num ());
		}/* end of inner parallel region */
	}/* end of outer parallel region */

	return 0;
}
