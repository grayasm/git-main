/*  Cap. 7 pag. 247
    Fig. 7.3 - Data Race Condition due to missing private declaration.

    The variables i and x are not explicitly declared as private.
    Variable i is implicitly declared to be private according to the OpenMP
    default data-sharing rules. Variable x is shared by default. It is written
    to by multiple threads, leading to a race condition.
*/


#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int n = 20;
	int i;
	double x, h = 1, sum = 0;

#pragma omp parallel for shared(h) reduction(+:sum)
	for (i=1; i<=n; i++)
	{
		x = h * ((double)i - 0.5);
		sum += x * x;
	}

	printf ("sum = %f , correct is= %f, result is %s\n",
	        sum, 2665.0, (sum == 2665. ? "ok":"not ok"));

	return 0;
}
