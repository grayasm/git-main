/* Schedule Clause is supported only for Loop constructs (for-loop).

   syntax: #pragma omp for schedule(kind [, chunk-size])

   The chunks are assigned to the threads statically in a round-robin manner,
   in the order of the thread number. The last chunk to be assigned may have
   a smaller number of iterations. When no chunk size is specified, the
   iteration space is divided into chunks that are approximately equal in size.
   Each thread is assigned at most one chunk.

   Round robin schedule : https://en.wikipedia.org/wiki/Round-robin_scheduling
   In short: queue with last-in last-processed.
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

#pragma omp parallel for private(i) shared(a) schedule(static, 2)
	for (i=0; i<MAX; ++i)
	{
		a[i] = omp_get_thread_num ();
		printf("i= %02d thread= %d\n", i, a[i]);

	}/* end of parallel region */

	return 0;
}
