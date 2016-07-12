/*  syntax:

    #pragma omp task [clause[[,] clause] ..] new-line
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


    When a final clause is present on a task construct and the final clause
    expression evaluates to true, the generated task will be a final task.
    All task constructs encountered during execution of a final task will
    generate final and included tasks. Note that the use of a variable in a
    final clause expression of a task construct causes an implicit reference
    to the variable in all enclosing constructs.

    tldr: task final means that all furter encountered tasks will be executed
          serialized by that thread. No new threads will be started.
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

#pragma omp task firstprivate(n) final(n<6)
    {
        printf ("n:%d t:%d\n", n, omp_get_thread_num ());
        ret = recursive (n-1);
    }/* end of task */

#pragma omp taskwait
    return ret;
}

/*
$> ./29_final
n:8 t:4
n:7 t:5
n:6 t:6
n:5 t:3  <-final
n:4 t:3
n:3 t:3
n:2 t:3
n:1 t:3
*/
