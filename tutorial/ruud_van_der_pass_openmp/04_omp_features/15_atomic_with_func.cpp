/* Synchronization construct: atomic

   See 15_atomic.cpp for header.

   Obs: the func() call is not atomic.
        The atomic construct does not stop func() from being executed parallel.
 */


#include <stdio.h>
#include <omp.h>

int func();
int main(int argc, char** argv)
{
    const int MAX=5;
    int i, a[MAX], sum;


#pragma omp parallel for shared(a, sum) private(i)
    for (i=0; i<MAX; i++)
    {
	    a[i] = i;

#pragma omp atomic
	    sum += (a[i] + func());

    }

    printf ("sum= %d\n", sum); // sum(0:4)=4*5/2 = 20/2 = 10;
    if (sum == 10) printf("OK\n");
    else           printf("Error\n");

    return 0;
}

int func()
{
	int t = omp_get_thread_num ();
	printf("in func() thread %d\n", t);
	return 0;
}
