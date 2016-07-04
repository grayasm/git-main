/* Cap7 pag 258
   Fig. 7.15 Example of a function call that is not thread-safe

   The library keeps track of how often its routines are called by incrementing
   a global counter. If executed by multiple threads within a parallel region,
   all threads read and modify the shared counter variable, leading to a race
   condition.
*/

#include <stdio.h>
#include <omp.h>

int icount;
void lib_func()
{
	icount++;
	// do_lib_work();
}


int main(int argc, char** argv)
{
	icount = 0;

#pragma omp parallel num_threads(32)
	{
		lib_func ();
	}/* end of parallel */

	printf ("icount=%d, correct is 32\n", icount);
	return 0;
}
