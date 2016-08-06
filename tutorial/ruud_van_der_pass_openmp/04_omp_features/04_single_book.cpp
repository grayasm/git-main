/*  The single construct specifies that the structured block immediatelly
    following it should be executed by one thread only.

    Syntax:

    #pragma omp parallel
    {
    #pragma omp single [clause [[,] clause ...]]
      {
        structured block
      }
    }
 */


#include <stdio.h>
#include <vector>
#include <omp.h>


int main(int argc, char** argv)
{
#pragma omp parallel
	{
#pragma omp single
		{
			printf("omp single th= %d\n", omp_get_thread_num ());
		}/* End of single block. */

#pragma omp for
		for(size_t i=0; i<4; ++i)
		{
			printf("omp for    th= %d\n", omp_get_thread_num ());
		}
	}/* End of parallel region. */

	return 0;
}
