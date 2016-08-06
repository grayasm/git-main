/* Schedule Clause is supported only for Loop constructs (for-loop).

   syntax: #pragma omp for schedule(kind [, chunk-size])

   The iterations are assigned to threads as the threads request them.
   The thread executes the chunk of iterations (controlled through the chunk
   size parameter), then requests another chunk until there are no more chunks
   to work on. The last chunk may have fewer iterations than chunk size.
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
	const int MAX=10;
	int i, a[MAX];

#pragma omp parallel for private(i) shared(a) schedule(dynamic, 2)
	for (i=0; i<MAX; ++i)
	{
		a[i] = omp_get_thread_num ();
		printf("i= %02d thread= %d\n", i, a[i]);

	}/* end of parallel region */

	return 0;
}
