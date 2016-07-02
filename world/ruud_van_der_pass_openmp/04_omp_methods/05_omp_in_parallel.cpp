/*  int omp_in_parallel(void);

    This function returns true if currently running in parallel, false otherwise.
    Here, true and false represent their language-specific counterparts.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    omp_set_num_threads (4);
    printf ("in parallel: %d\n", omp_in_parallel ());

#pragma omp parallel
#pragma omp master
    {
        printf ("in parallel: %d\n", omp_in_parallel ());
    }/* end of parallel */

    return 0;
}

/*
$> ./05_omp_in_parallel
in parallel: 0
in parallel: 1
*/
