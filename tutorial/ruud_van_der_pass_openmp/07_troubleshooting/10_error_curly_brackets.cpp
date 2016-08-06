/*  Cap7. pag 256
    Figure 7.14: Example of the impact of curly brackets on parallel execution

    It is very likely an error was made in the definition of the second parallel
    region: function work2 is executed by the master thread only.
*/

#include <stdio.h>
#include <omp.h>


void work1 ();
void work2 ();

int main(int argc, char** argv)
{

#pragma omp parallel num_threads(2)
	{
		work1 (); /*-- Executed in parallel --*/
		work2 (); /*-- Executed in parallel --*/
	}/* end of parallel */

#pragma omp parallel num_threads(2)
	work1 (); /*-- Executed in parallel --*/
	work2 (); /*-- Executed sequentially --*/

	return 0;
}

void work1 (){ printf ("work1 () in thread=%d\n", omp_get_thread_num ()); }
void work2 (){ printf ("work2 () in thread=%d\n", omp_get_thread_num ()); }
