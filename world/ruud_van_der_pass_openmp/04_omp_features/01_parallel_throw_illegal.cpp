/* cap.4 pag 56
   In C++ there is an additional constraint. A throw inside a parallel region
   must cause execution to resume within the same parallel region, and it must
   be caught by the same thread that threw the exception.

   Throw from parallel region and catch outside -> execution Aborted.
*/

#include <stdio.h>
#include <omp.h>


void function()
{
#pragma omp parallel
	{
		int thid = omp_get_thread_num ();
		printf("The parallel region is executed by thread %d\n", thid);

		if (thid == 2)
		{
			printf("  Thread 2 throws exception\n");
			throw "illegal";
		}
	}
/* End of parallel region. */
}



int main(int argc, char** argv)
{
	try
	{
		function (); // throws <const char*>
	}
	catch(const char* msg)
	{
		printf("Caught exception \"%s\" in main\n", msg);
	}

	printf("Returning clean\n");
	return 0;
}
