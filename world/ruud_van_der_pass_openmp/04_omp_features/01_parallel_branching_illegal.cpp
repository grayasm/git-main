/* Cap.4 pag 56 - restrictions on the parallel construct and its clauses:

   A program that branches into or out of a parallel region is nonconforming.
   In other words, if a program does so, then it is illegal, and the behavior is
   undefined.
*/

#include <stdio.h>
#include <omp.h>


void function()
{
#pragma omp parallel
	{
		int thid = omp_get_thread_num();

		printf("The parallel region is executed by thread %d\n", thid);
		if (thid == 2)
			return;
	}
/* End of parallel region. */
}


int main(int argc, char** argv)
{
	function ();
	return 0;
}
