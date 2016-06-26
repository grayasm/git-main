/* Use of private clause with a parallel for construct.
   The syntax: private(list)

   Each thread has its own value for a private variable.
   It is stored on the thread stack.
   This data is undefined before and after exiting the specific construct.
*/

#include <stdio.h>
#include <vector>
#include <omp.h>


int main(int argc, char** argv)
{
	int i, a, MAX=5;

#pragma omp parallel for private(i,a)
    for (i=0; i<MAX; i++)
    {
	    a = i + 1;
	    printf("thread %d over i= %d has a= %d\n", omp_get_thread_num(),i,a);

    } /* End of parallel region. */


    printf("outside parallel i= %d a= %d\n", i,a);
    // sequential i= 5 a= 5
    // parallel   i= 0 a= 0  (undefined)

    return 0;
}
