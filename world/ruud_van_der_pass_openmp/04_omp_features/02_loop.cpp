/* 4.4.1 Loop Construct

   #pragma omp for [clause[[,] clause]. . . ]
           for-loop

  The loop construct causes the iterations of the loop immediately following it
  to be executed in parallel. At run time, the loop iterations are distributed
  across the threads.
  This is probably the most widely used of the work-sharing features.
 */


#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
	int i=0, MAX=5;

#pragma omp parallel private(i)
	{
        #pragma omp for
		for(i=0; i<MAX; ++i)
		{
			printf("omp for (i %d thread %d)\n",i, omp_get_thread_num());
		}
		/* End of Loop. */


		printf("omp parallel (thread %d)\n", omp_get_thread_num());
	}
/* End of parallel region. */

	printf("Returning clean...\n");
	return 0;
}
