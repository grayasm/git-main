/* The syntax is lastprivate(list )
   It ensures that the last value of a data object listed is accessible after
   the corresponding construct has completed execution.

   The object will have the value from the iteration of the loop (if a for loop)
   or the sections's section that would be last in a sequential execution.
*/



#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	int i, a, MAX=5;

#pragma omp parallel for private(i) lastprivate(a)
    for (i=0; i<MAX; i++)
    {
        a = i+1;
        printf("thread %d over i=%d has a= %d\n", omp_get_thread_num(),i,a);
    } /* End of parallel region. */


    printf("after parallel i=%d a= %d\n", i, a);
    // sequential, i=5, a=5
    // parallel,   i=0, a=5

    return 0;
}
