/*  The if clause is supported on the parallel construct only, where it is used
    to specify conditional execution.

    syntax: if(scalar-logical-expression )

    If the logical expression evaluates to true, which means it is of type
    integer and has a non-zero value in C/C++, the parallel region will be
    executed by a team of threads.
    If it evaluates to false, the region is executed by a single thread only,
    and therefore it is an **inactive** parallel region.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    const int MAX=4;
    int i, a[MAX];

#pragma omp parallel if(MAX > 8) shared(a) private(i) // if(false)
    {

#pragma omp for
        for (i=0; i<MAX; ++i)
        {
	        a[i] = omp_get_thread_num ();
	        printf ("thread %d over i= %d\n", a[i], i);

        }/* end of parallel region */
    }


    return 0;
}
