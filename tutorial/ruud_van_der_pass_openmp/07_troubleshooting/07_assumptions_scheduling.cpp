/*  Cap7 pag 253 - 7.2.5 Assumptions about Work Scheduling.

    The nowait clause might potentially introduce a data race condition,
    even with static work scheduling, if n is not a multiple of the number
    of threads.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    const int n=15;
    int i, a[n], b[n], c[n];
    for (i=0; i<n; i++)
        a[i] = i;

#pragma omp parallel
    {
#pragma omp for schedule(static) nowait
        for (i=0; i<n; i++)
        {
            b[i] = a[i] * 2;
        }


#pragma omp for schedule(static) nowait
        for (i=0; i<n; i++)
        {
            c[i] = b[i] / 2;
        }
    }/* end of parallel */


    for (i=0; i<n; i++)
        printf ("c[%d]=%d , correct is=%d\n", i, c[i], i);

    return 0;
}
