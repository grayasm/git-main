/* pag 55, Fig 4.3 Example of a parallel region

   added the sample only because the region is empty (strange enough).
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{

#pragma omp parallel
	{
		printf("The parallel region is executed by thread %d\n",
		       omp_get_thread_num ());

		if (omp_get_thread_num() == 2) {
			printf("  Thread %d does things differently\n",
			       omp_get_thread_num ());
		}
	}
/* End of parallel region */


	return 0;
}
