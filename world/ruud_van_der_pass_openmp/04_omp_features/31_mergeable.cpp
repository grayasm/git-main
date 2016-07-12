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

  When a mergeable clause is present on a task construct, and the generated task
  is an undeferred task or an included task, the implementation might generate
  a merged task instead.

  The final clause is most effective when used in conjunction with the mergeable
  clause since all tasks created in a final task region are included tasks that
  can be merged if the mergeable clause is present.
 */



#include <stdio.h>
#include <omp.h>

int recursive (int n);

int main(int argc, char** argv)
{
    const int N=8;

#pragma omp parallel num_threads(8)
    {
#pragma omp single
        {
            recursive (N);

        }/* end of single */
    }/* end of parallel */

    return 0;
}

int recursive (int n)
{
    int ret;
    if (n <= 0)
        return n;

#pragma omp task firstprivate(n) final(n<6) mergeable
    {
        printf ("n:%d t:%d\n", n, omp_get_thread_num ());
        ret = recursive (n-1);
    }/* end of task */

#pragma omp taskwait
    return ret;
}

/*
$>  ./31_mergeable
n:8 t:0
n:7 t:2
n:6 t:6
n:5 t:7 <- final, all merged
n:4 t:7
n:3 t:7
n:2 t:7
n:1 t:7
*/
