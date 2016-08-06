/*
  #pragma omp for [clause ...]  newline
                  schedule (type [,chunk])
                  ordered
                  private (list)
                  firstprivate (list)
                  lastprivate (list)
                  shared (list)
                  reduction (operator: list)
                  collapse (n)
                  nowait

   Specifies how many loops in a nested loop should be collapsed into one large
   iteration space and divided according to the schedule clause.
   The sequential execution of the iterations in all associated loops
   determines the order of the iterations in the collapsed iteration space.
 */


#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{

/*  Good explanation
    http://stackoverflow.com/questions/28482833/understanding-the-collapse-clause-in-openmp

    a) If execution of any associated loop changes any of the values used to
       compute any of the iteration counts, then the behavior is unspecified.

       Undefined behavior example:
       #pragma omp parallel for private(j) collapse(2)
               for (i=0; i < 4; i++)
                   for (j=0; j<i; j++)   <- unspecified behavior
                       { ... }

    b) Correct example:
       #pragma omp parallel for private(j) collapse(2)
               for (i=0; i < 4; i++)
                   for (j=0; j < 100; j++)
                       { ... }

       - without collapse only 4 threads will be active, the rest will be wasted
       - with collapse, 400 iterations will be distributed among all threads
       - without collapse on 4 threads the load will not be well distributed
*/

	const int m=2, n=3, o=4;
	int i, j, k, a[m][n][o];

#pragma omp parallel for shared(a) private(i,j,k) collapse(3)
	for (i=0; i < m; i++)
		for (j=0; j < n; j++)
			for (k=0; k < o; k++)
			{
				a[i][j][k] = omp_get_thread_num ();
				printf ("%d %d %d %d\n", i, j, k, a[i][j][k]);

			}/* end of parallel region */

	return 0;
}
