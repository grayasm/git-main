/* Cap7. pag 253 Fig 7.10 Example of incorrect nested directive.

   Nested parallelism is implemented at the level of parallel regions,
   not work-sharing constructs, as erroneously attempted in this code fragment.
*/


#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    const int n=15;
    int i, j, a[n], b[n][n];

#pragma omp parallel shared(a,b)
    {

#pragma omp for
        for (i=0; i<n; i++)
        {
            a[i] = i + 1;

#pragma omp for   // WRONG - Needs a new parallel region.
            for (j=0; j<n; j++)
            {
                b[i][j] = a[i] + 1;
            }
        }
    }/* end of parallel */

    return 0;
}
