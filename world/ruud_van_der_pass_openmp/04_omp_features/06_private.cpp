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
	size_t i;
	std::vector<int> a(5, 0);

#pragma omp parallel for shared(a) private(i)
    for (i=0; i<a.size(); i++)
    {
        a[i] += omp_get_thread_num ();
        printf("thread %d over i= %d\n", omp_get_thread_num(), i);

    } /* End of parallel region. */

    return 0;
}
