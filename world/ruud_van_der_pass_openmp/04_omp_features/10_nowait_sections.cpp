/* The nowait clause will make a thread continue over a barrier that exists
   at the end of a construct.

   However, that the barrier at the end of a parallel region cannot be
   suppressed.

   Example: #pragma omp sections nowait
*/

#include <stdio.h>
#include <omp.h>
#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32

void func(int sec, bool todelay);

int main(int argc, char** argv)
{

#pragma omp parallel
    {
#pragma omp sections nowait
	    {
#pragma omp section
		    func(1, omp_get_thread_num() > 2);
#pragma omp section
		    func(2, omp_get_thread_num() > 2);
#pragma omp section
		    func(3, omp_get_thread_num() > 2);
#pragma omp section
		    func(4, omp_get_thread_num() > 2);
#pragma omp section
		    func(5, omp_get_thread_num() > 2);
	    }/* end of sections */

	    printf("thread %d ended\n", omp_get_thread_num());
    }/* end of parallel region */

    return 0;
}


void func(int sec, bool todelay)
{
	if(todelay) sleep(1);
	printf("thread %d section %d %s\n", omp_get_thread_num(), sec,
	       (todelay == true? "\tslept" : "nowait"));
}
