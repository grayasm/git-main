/* Synchronization construct: critical

   syntax: #pragma omp critical [name]
              structured-block

   The critical construct provides a means to ensure that multiple threads do
   not attempt to update the same shared data simultaneously.  The associated
   code is referred to as a critical region, or a critical section.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int MAX=5;
	int i, a[MAX], sum=0, max=-1;

#pragma omp parallel for shared(a, sum, max) private(i)
	for (i=0; i<MAX; i++)
	{
		a[i] = i;

#pragma omp critical (sum_and_max)
		{
			sum += a[i];
			if (a[i] > max) max = a[i];
		}
	}

	// sum(0:4)=4*5/2 = 20/2 = 10;
	printf ("sum= %d max= %d\n", sum, max);
	if (sum == 10 && max == 4) printf("OK\n");
	else                       printf("Error\n");

	return 0;
}
