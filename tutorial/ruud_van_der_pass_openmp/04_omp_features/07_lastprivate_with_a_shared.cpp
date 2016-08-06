/*  About lastprivate(list )

    In fact, all this clause really does is provide some extra convenience,
    since the same functionality can be implemented by using an additional
    shared variable and some simple logic.
*/



#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	int i, a, a_shared, MAX=5;

#pragma omp parallel for private(i) private(a) shared(a_shared)
    for (i=0; i<MAX; i++)
    {
        a = i+1;
        printf("thread %d over i=%d has a= %d\n", omp_get_thread_num(),i,a);
        if (i == MAX-1) a_shared = a;

    } /* End of parallel region. */


    printf("after parallel i=%d a= %d a_shared= %d\n", i, a, a_shared);
    // sequential i= 5 a= 5  a_shared= 5
    // parallel   i= 0 a= 0  a_shared= 5

    return 0;
}
