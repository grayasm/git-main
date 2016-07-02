/*  void omp_set_max_active_levels(int max_levels);

    This function limits the maximum allowed number of nested, active parallel
    regions.
*/

#include <stdio.h>
#include <omp.h>


void recursive (int level);
int main(int argc, char** argv)
{
    omp_set_nested (1);
    omp_set_max_active_levels (3);

    recursive (4);

    return 0;
}

void recursive (int level)
{
#pragma omp parallel shared(level)
#pragma omp master
    {
        printf ("parallel, level=%d threads=%d\n", level,omp_get_num_threads());

        if (level > 0)
            recursive (level -1);
    }/* end of parallel */
}

/*
$> ./14_omp_set_max_active_levels
parallel, level=4 threads=10
parallel, level=3 threads=10
parallel, level=2 threads=10
parallel, level=1 threads=1
parallel, level=0 threads=1
*/
