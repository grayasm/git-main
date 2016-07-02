/*  void omp_set_num_threads(int num_threads);

    Specifies the number of threads used by default in subsequent parallel
    sections, if those do not specify a num_threads clause. The argument of
    omp_set_num_threads shall be a positive integer.

    int omp_get_num_threads(void);

    Returns the number of threads in the current team.
    In a sequential section of the program omp_get_num_threads returns 1.
*/


#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
    omp_set_num_threads (4);

    printf ("main: %d\n", omp_get_num_threads ());

#pragma omp parallel
#pragma omp master
    {
        printf ("master: %d\n", omp_get_num_threads ());
    }/* end of parallel */

    printf ("main: %d\n", omp_get_num_threads ());

#pragma omp parallel num_threads(3)
#pragma omp master
    {
        printf ("master: %d\n", omp_get_num_threads ());
    }/* end of parallel */

    printf ("main: %d\n", omp_get_num_threads ());
}

/*
$> ./01_omp_set_num_threads
main: 1
master: 4
main: 1
master: 3
main: 1
*/
