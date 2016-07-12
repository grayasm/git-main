/*
  syntax:

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


    A thread that encounters a task scheduling point within the task region may
    temporarily suspend the task region. By default, a task is tied and its
    suspended task region can only be resumed by the thread that started its
    execution. If the untied clause is present on a task construct, any thread
    in the team can resume the task region after a suspension. The untied clause
    is ignored if a final clause is present on the same task construct and the
    final clause expression evaluates to true, or if a task is an included task.

    tldr: a task child of a parent task is tied (bounded) to the parent that
          started it, and can be suspended and resummed only by the parent
          UNLESS the child has "untied" clause.

          In the example below 2 task threads are running in parallel,
          the parent and the untied child.
 */

#include <stdio.h>
#include <omp.h>
#ifdef WIN32
#include <windows.h>
#define sleep(a) Sleep(a*1000)
#else //linux
#include <unistd.h>
#endif //WIN32

void taskrun (int v);

int main(int argc, char** argv)
{
	const int N=2;

#pragma omp parallel num_threads(8)
	{
#pragma omp single nowait
		{
			taskrun (N);
		}/* end of single */
	}/* end of parallel */

	return 0;
}


void taskrun (int v)
{
	if (v <= 0)
		return;

#pragma omp task untied firstprivate(v)
	{
		taskrun (v-1);

		for (int i=0; i<3; i++)
		{
			sleep (1);
			printf ("v:%d t:%d i:%d\n", v, omp_get_thread_num (), i);
		}
	}/* end of task */
}


/*
$> ./30_untied
v:2 t:5 i:0
v:1 t:7 i:0
v:2 t:5 i:1
v:1 t:7 i:1
v:2 t:5 i:2
v:1 t:7 i:2
*/
