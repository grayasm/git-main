/*  void omp_set_dynamic(int dynamic_threads);

    Enable or disable the dynamic adjustment of the number of threads within
    a team. The function takes the language-specific equivalent of true and
    false, where true enables dynamic adjustment of team sizes and false
    disables it.

    A value that indicates if the number of threads available in subsequent
    parallel region can be adjusted by the runtime. If nonzero, the runtime can
    adjust the number of threads, if zero, the runtime will not dynamically
    adjust the number of threads.

    The number of threads will never exceed the value set by omp_set_num_threads
    or by OMP_NUM_THREADS.
    The setting for omp_set_dynamic will override the setting of the
    OMP_DYNAMIC environment variable.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    omp_set_dynamic (9);
    omp_set_num_threads (4);
    printf ("dynamic: %d\n", omp_get_dynamic ());

#pragma omp parallel
#pragma omp master
    {
        printf ("dynamic: %d\n", omp_get_dynamic ());
    }/* end of parallel */

    return 0;
}

/*
$> ./06_omp_set_dynamic
dynamic: 1
dynamic: 1
*/
