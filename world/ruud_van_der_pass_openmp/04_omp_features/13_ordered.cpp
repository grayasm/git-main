/* Synchronization construct:  "ordered"

   Allows one to execute a structured block within a parallel loop in sequential
   order. This is sometimes used, for instance, to enforce an ordering on the
   printing of data computed by different threads.
   It may also be used to help determine whether there are any data races
   in the associated code.

   syntax: #pragma omp ordered
              structured-block

   Ex: without ordered threads are scheduled in random order: 3,5,0,1,4,2
       with ordered construct threads are scheduled in order: 0,1,2,3,4,5
*/

#include <stdio.h>
#include <omp.h>



int main(int argc, char** argv)
{
	const int MAX=5;
	int i, a[MAX];

#pragma omp parallel for shared(a) private(i) ordered
	for (i=0; i<MAX; i++)
	{
		// threads scheduled in random order
		a[i] = omp_get_thread_num ();
		printf ("parallel i= %d th= %d\n", i, a[i]);

#pragma omp ordered
		{
			// thread scheduled by their number order
			printf ("ordered  i= %d th= %d\n", i, omp_get_thread_num());
		}

	}/* end of parallel region */

	return 0;
}
