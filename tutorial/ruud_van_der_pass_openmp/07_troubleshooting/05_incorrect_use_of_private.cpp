/*  Cap7. pag 250 - Fig 7.6 - Incorrect use of the private clause.

    This code has two problems.
    First, variable b is used but not initialized within the parallel loop.
    Second, variables a and b should not be used after the parallel loop.
    The values after the parallel loop are undefined and therefore
    implementation dependent.
 */

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int n=10;
	int i, a, b, c;

#pragma omp parallel for private(i,a,b)
	for (i=0; i<n; i++)
	{
		b++;
		a = b + i;
	}/* end of parallel */
	c = a + b;


	printf ("a= %d , correct is = %d\n"
	        "b= %d , correct is = %d\n"
	        "c= %d , correct is = %d\n",
	        a,19,b,10,c,29);

	return 0;
}
