/*  int omp_get_team_size(int level);

    The omp_get_team_size routine returns, for a given nested level of the
    current thread, the size of the thread team to which the ancestor or the
    current thread belongs.
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
            int level = omp_get_level ();
            int tmsz = omp_get_team_size(1);

            printf ("var=%d level=%d thread: %d has at level1 team size: %d\n",
                    var, level, tid, tmsz);
        }/* end of single */

#pragma omp single
        {
            if (var > 0)
                recursive (var -1);
        }/* end of single */
    }/* end of parallel */
}

/*
$>  ./17_omp_get_team_size
var=3 level=1 thread: 1 has at level1 team size: 4
var=2 level=2 thread: 3 has at level1 team size: 4
var=1 level=3 thread: 0 has at level1 team size: 4
var=0 level=4 thread: 0 has at level1 team size: 4
*/
