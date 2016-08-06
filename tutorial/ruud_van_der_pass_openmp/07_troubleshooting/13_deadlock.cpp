/* Cap7 pag 268,   7.3.5 Deadlock Situations
   Figure 7.22: Example of a deadlock situation

   If executed by two threads, this program never finishes.
   The thread executing work1 waits forever in the explicit barrier.
   The other thread waits in vain for the other thread to arrive in the implicit
   barrier at the end of the parallel sections construct.
 */

#include <stdio.h>
#include <omp.h>


void work1()
{
	/*-- some work performed here --*/
	printf ("work1 () thread=%d  + barrier\n", omp_get_thread_num ());
#pragma omp barrier
}


void work2()
{
	/*-- some work performed here --*/
	printf ("work2 () thread=%d\n", omp_get_thread_num ());
}


int main(int argc, char** argv)
{

#pragma omp parallel sections
	{
#pragma omp section
		work1 ();

#pragma omp section
		work2 ();

	}/* end of parallel */

	return 0;
}
