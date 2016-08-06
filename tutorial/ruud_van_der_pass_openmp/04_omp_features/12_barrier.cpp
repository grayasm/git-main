/* Synchronization construct: "barrier"

   syntax: #pragma omp barrier

   A barrier is a point in the execution of a program where threads wait for
   each other: no thread in the team of threads it applies to may proceed
   beyond a barrier until all threads in the team have reached that point.
 */

#include <stdio.h>
#include <omp.h>
#include <ctime>

#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32


int main(int argc, char* argv[])
{
    int t;

#pragma omp parallel private(t)
    {
        t = omp_get_thread_num ();
        if (t > 2) sleep(1);

        printf ("thread %d at barrier %s\n", t, (t>2 ? "\tslept" : ""));

#pragma omp barrier

        printf ("thread %d passed\n", t);

    }/* end of parallel */

    return 0;
}
