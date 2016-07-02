/*  int omp_get_ancestor_thread_num(int level);

    Returns the thread number of the ancestor of the current thread at a given
    nested level. Returns -1 if the nested level is not within the range of
    0 and the current thread's nested level as returned by omp_get_level.
*/


#include <stdio.h>
#include <omp.h>


void recursive (int level);
int main(int argc, char** argv)
{
    omp_set_nested (1);

    recursive (3);

    printf ("\n");

    return 0;
}

void recursive (int var)
{
#pragma omp parallel shared(var) num_threads(4)
    {
#pragma omp single
        {
            int tid = omp_get_thread_num ();
            int anc = omp_get_ancestor_thread_num (1);
            int level = omp_get_level ();

            printf ("var=%d level=%d thread: %d has at level1 ancestor: %d\n",
                    var, level, tid, anc);
        }/* end of single */

#pragma omp single
        {
            if (var > 0)
                recursive (var -1);
        }/* end of single */
    }/* end of parallel */
}

/*
$> ./16_omp_get_anchestor_thread_num
var=3 level=1 thread: 1 has at level1 ancestor: 1
var=2 level=2 thread: 3 has at level1 ancestor: 3
var=1 level=3 thread: 2 has at level1 ancestor: 3
var=0 level=4 thread: 0 has at level1 ancestor: 3
*/
