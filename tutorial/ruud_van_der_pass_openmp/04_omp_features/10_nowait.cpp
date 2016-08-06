/* The nowait clause will make a thread continue over a barrier that exists
   at the end of a construct.

   However, that the barrier at the end of a parallel region cannot be
   suppressed.

   Example: #pragma omp for nowait
*/

#include <stdio.h>
#include <omp.h>
#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32


int main(int argc, char** argv)
{
    const int MAX=6;
    int i, j, a[MAX], b[MAX];
    for (i=0; i<MAX; i++) a[i] = b[i] = -1;


#pragma omp parallel shared(a,b) private(i,j)
    {
#pragma omp for nowait
        for (i=0; i<MAX; i++)
        {
            a[i] = omp_get_thread_num ();
            if(i > 3) sleep(1); // delayed on purpose
            printf("for 1 thread %d %s\n", a[i], (i>3?"\tslept":"nowait"));
        }

#pragma omp for
        for (j=0; j<MAX; j++)
        {
            b[j] = omp_get_thread_num ();
            printf("for 2 thread %d\n", b[j]);
        }
    }

    return 0;
}
