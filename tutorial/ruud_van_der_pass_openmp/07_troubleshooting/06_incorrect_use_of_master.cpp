/*  Cap7 - Figure 7.8: Incorrect use of the master construct

    This code fragment implicitly assumes that variable Xinit is available to
    the threads after initialization.
    This is incorrect.
    The master thread might not have executed the assignment when another thread
    reaches it, or the variable might not have been flushed to memory.
 */

#include <stdio.h>
#include <omp.h>
#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32


int main(int argc, char** argv)
{
	int Xinit, Xlocal;

#pragma omp parallel shared(Xinit) private(Xlocal)
	{
#pragma omp master
		{
			sleep(1);
			Xinit = 10;
		}

		Xlocal = Xinit; /*-- Xinit might not be available yet --*/
		printf ("thread=%d Xinit=%d\n", omp_get_thread_num (), Xinit);

	}/* end of parallel */


	return 0;
}
