/*  int omp_get_active_level(void);

    This function returns the nesting level for the active parallel blocks,
    which enclose the calling call.
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
    {
#pragma omp single
        {
            printf ("var=%d thread=%d of %d active level=%d \n",
                    var, omp_get_thread_num(), omp_get_num_threads(),
                    omp_get_active_level ());

        }/* end of single */

#pragma omp single
        {
            if (var > 0)
                recursive (var -1);
        }/* end of single */
    }/* end of parallel */
}
