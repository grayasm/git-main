/* Schedule Clause is supported only for Loop constructs (for-loop).

   syntax: #pragma omp for schedule(kind [, chunk-size])

   The iterations are assigned to threads as the threads request them.
   The thread executes the chunk of iterations (controlled through the chunk
   size parameter), then requests another chunk until there are no more chunks
   to work on. For a chunk size of 1, the size of each chunk is proportional
   to the number of unassigned iterations, divided by the number of threads,
   decreasing to 1.
   For a chunk size of “k” (k > 1), the size of each chunk is determined in
   the same way, with the restriction that the chunks do not contain fewer
   than k iterations (with a possible exception for the last chunk to be
   assigned,  which may have fewer than k iterations).
   When no chunk size is specified, it defaults to 1.
*/

#include <stdio.h>
#include <omp.h>
#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32



int main(int argc, char* argv[])
{
	const int MAX=20;
	int i, a[MAX];

#pragma omp parallel for private(i) shared(a) schedule(guided)
	for (i=0; i<MAX; ++i)
	{
		a[i] = omp_get_thread_num ();
		printf("i= %02d thread= %d\n", i, a[i]);

	}/* end of parallel region */

	return 0;
}
