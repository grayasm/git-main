/*  If a thread in a team executing a parallel region encounters another
    parallel construct, it creates a new team and becomes the master of that
    new team. This is generally referred to in OpenMP as “nested parallelism.”

    This API feature is implementation defined, thus Solaris or some other BSD
    is free to not provide parallelism. It means the nested parallel region
    will be inactive/ignored/serialized/executed by a single thread.
*/


#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    omp_set_nested (1);
    printf ("nested parallelism is %s\n",
            omp_get_nested () ? "supported" : "not supported");


    int tid;

#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num ();
        printf ("thread %d - outer parallel region\n", tid);

#pragma omp parallel num_threads(2) firstprivate(tid)
        {
	        printf ("\tTID %d: thread %d - inner parallel region\n",
	                tid, omp_get_thread_num ());

        }/* end of inner parallel region */
    }/* end of outer parallel region */

    return 0;
}
