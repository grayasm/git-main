/* Synchronization construct: master

   syntax: #pragma omp master
             structured-block

   The master construct defines a block of code that is guaranteed to be
   executed by the master thread only.
   It is thus similar to the single construct.
   The master construct is technically not a work-sharing construct, however,
   and it **does not** have an implied barrier on entry or exit.
*/


#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int MAX=5;
	int i, a[MAX];


#pragma omp parallel
	{
#pragma omp for
		for (i=0; i<MAX; i++)
			a[i] = i + 100;

#pragma omp master
		{
			for (i=0; i<MAX; i++)
				printf ("a[%d]= %d thread= %d\n", i,a[i],omp_get_thread_num());
		}/* end of master does not have a barrier */

#pragma omp barrier


#pragma omp for
		for (i=0; i<MAX; i++)
			a[i] += 100;

	}/* end of parallel region */

	return 0;
}
