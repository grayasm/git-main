/*
 syntax:
        #pragma omp task [clause [[,] clause] ...] new-line
            structured-block

            [clause]=
            if (scalar-expr)
            final (scalar-expr)
            untied
            default (shared | none)
            mergeable
            private (list)
            firstprivate (list)
            shared (list)

  The taskyield construct specifies that the current task can be suspended in
  favor of execution of a different task.

  The taskyield directive may be placed only at a point where a base language
  statement is allowed. The taskyield directive may not be used in place of the
  statement following an if, while, do, switch, or label.
*/


#include <stdio.h>
#include <omp.h>

#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32


int main(int argc, char** argv)
{
    omp_lock_t lk;
    omp_init_lock (&lk);

#pragma omp parallel
    {
#pragma omp single nowait
        {
            for (int i=0; i<3; i++)
#pragma omp task firstprivate(i)
            {
                while (!omp_test_lock (&lk))
                {
                    printf ("i:%d t:%d yield\n", i, omp_get_thread_num());
#pragma omp taskyield
                }

                printf ("i:%d t:%d working\n", i, omp_get_thread_num ());
                sleep(1);
                omp_unset_lock (&lk);

            }/* end of task */
        }/* end of single */
    }/* end of parallel */

    omp_destroy_lock (&lk);

    return 0;
}

/*
$> ./32_taskyield
i:0 t:7 working
i:2 t:9 yield
i:2 t:9 yield
i:2 t:9 yield
...
i:2 t:9 working
i:1 t:0 yield
i:1 t:0 yield
...
i:1 t:0 yield
i:1 t:0 working
 */
