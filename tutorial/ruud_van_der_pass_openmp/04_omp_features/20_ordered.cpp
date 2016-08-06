/*  The ordered clause is rather special: it does not take any arguments and is
    supported on the loop construct only.

    It has to be given if the ordered construct is used in a parallel
    region, since its purpose is to inform the compiler of the presence
    of this construct.

    #pragma omp parallel for ordered
    for (...)
    {
    // thread scheduled in random  order: 5,1,2,4,0..

    #pragma omp ordered
    {
    // threads scheduled by their number: 0,1,2,3,4,5..
    }

    } // end of parallel region
*/


#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int MAX=5;
	int i, a[MAX];

#pragma omp parallel for shared(a) private(i) schedule(dynamic) ordered
	for (i=0; i<MAX; i++)
	{
		a[i] = omp_get_thread_num ();
		printf ("in parallel a[%d]= %d\n", i, a[i]);

#pragma omp ordered
		{
			// debugging in sequential order
			printf ("in ordered  a[%d]= %d\n", i, a[i]);
		}

	}/* end of parallel for */

	return 0;
}
