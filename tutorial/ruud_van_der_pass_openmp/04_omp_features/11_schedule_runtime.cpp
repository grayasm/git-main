/* Schedule Clause is supported only for Loop constructs (for-loop).

   syntax: #pragma omp for schedule(kind [, chunk-size])

   If this schedule is selected, the decision regarding scheduling kind is made
   at run time. The schedule and (optional) chunk size are set through the
   OMP_SCHEDULE environment variable
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

#pragma omp parallel for private(i) shared(a) schedule(runtime)
	for (i=0; i<MAX; ++i)
	{
		a[i] = omp_get_thread_num ();
		printf("i= %02d thread= %d\n", i, a[i]);

	}/* end of parallel region */

	return 0;
}
