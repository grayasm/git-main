/*  void omp_set_nested(int nested);

    Enable or disable nested parallel regions, i.e., whether team members are
    allowed to create new teams. The function takes the language-specific
    equivalent of true and false, where true enables dynamic adjustment of team
    sizes and false disables it.

    If nonzero, enables nested parallelism. If zero, disables nested parallelism.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{

    omp_set_nested (1);
    omp_set_num_threads (4);

    printf ("nested: %d\n", omp_get_nested ());

#pragma omp parallel
#pragma omp master
    {
	    printf ("nested: %d\n", omp_get_nested ());
    }/* end of parallel */

    return 0;
}

/*
$> ./07_omp_set_nested
nested: 1
nested: 1
*/
