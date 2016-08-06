/* syntax: firstprivate(list )

   The firstprivate variables are initialized by the master thread before
   the team of threads are forked, with the values they had before the
   omp construct.

   Because a shared variable is initialized at the entry of the parallel
   region, a fistprivate variable looks similar with that, except that it is
   private for each thread. So there is a difference.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int MAX=7;
	int a[MAX], i, p;
	for (i=0; i<MAX; ++i) a[i] = -1;

	p = 3;

#pragma omp parallel shared(a) firstprivate(p)
	{
		int tid = omp_get_thread_num ();
		p += tid;
		if (p < MAX) a[p] = tid;

		printf("thread %d p= %d\n", tid, p);

	}/* End of parallel region. */


	for (i=0; i<MAX; i++)
		printf("outside a[%d]= %d\n", i, a[i]);

	return 0;
}
