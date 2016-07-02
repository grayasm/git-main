/*  int omp_get_level(void);

    This function returns the nesting level for the parallel blocks, which
    enclose the calling call.
*/

#include <stdio.h>
#include <omp.h>


void recursive (int level);
int main(int argc, char** argv)
{
    omp_set_nested (1);

    recursive (4);

    return 0;
}

void recursive (int var)
{
#pragma omp parallel shared(var)
#pragma omp master
    {
        printf ("parallel, var=%d level=%d\n", var, omp_get_level());

        if (var > 0)
            recursive (var -1);
    }/* end of parallel */
}

/*
$> ./15_omp_get_level
parallel, var=4 level=1
parallel, var=3 level=2
parallel, var=2 level=3
parallel, var=1 level=4
parallel, var=0 level=5
*/
