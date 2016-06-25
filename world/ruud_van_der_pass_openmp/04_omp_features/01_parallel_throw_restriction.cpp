/* cap.4 pag 56
   In C++ there is an additional constraint. A throw inside a parallel region
   must cause execution to resume within the same parallel region, and it must
   be caught by the same thread that threw the exception.
*/

#include <stdio.h>
#include <omp.h>


void function()
{
#pragma omp parallel
	{
		try
		{
			int thid = omp_get_thread_num ();
			printf("The parallel region is executed by thread %d\n", thid);

			if (thid == 2)
				throw 100;
		}
		catch(int e)
		{
			printf("Caught exception %d in parallel region in thread %d\n",
			       e, omp_get_thread_num ());
		}
	}
/* End of parallel region. */
}



int main(int argc, char** argv)
{
	function ();
	return 0;
}
