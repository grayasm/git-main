/*  By default, global data is shared, which is often appropriate. But in some
    situations we may need, or would prefer to have, private data that persists
    throughout the computation.
    The effect of the threadprivate directive is that the named global-lifetime
    objects are replicated, so that each thread has its own private "local" copy.

    syntax: #pragma omp threadprivate (list)
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int *pglobal;
#pragma omp threadprivate (pglobal)

int calculate_sum(int length);
int main(int argc, char** argv)
{
    const int n=5;
    int length[n] = {0,1,2,3,4};
    int i,j,sum=0,tid;


#pragma omp parallel for shared(length) private(tid,i,j,sum)
    for (i=0; i<n; i++)
    {
        tid = omp_get_thread_num ();

        if ((pglobal = (int*) malloc(length[i] * sizeof(int))) != NULL)
        {
            for (j=sum=0; j<length[i]; j++)
                pglobal[j] = j + 1;

            sum = calculate_sum (length[i]);
            printf ("TID %d: value of sum for i=%d is %d\n", tid,i,sum);
            free (pglobal);
        }
        else
        {
            printf ("TID %d: fatal error in malloc - length[%d]=%d\n",
                    tid, i, length[i]);
        }
    }/* end of parallel for */


    return 0;
}


int calculate_sum(int length)
{
    int sum = 0;
    for (int j=0; j<length; j++)
        sum += pglobal[j];

    return (sum);
}
