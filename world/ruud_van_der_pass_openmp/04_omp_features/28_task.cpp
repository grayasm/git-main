/*  A task construct defines an explicit task.

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

    - omp task will spawn a new thread for the following structured-block
    - task was designed to iterate over trees or double-linked lists
    - task is regullary used within a omp single construct so that only one
      thread is used initially to spawn different tasks
    - threads are assigned as they are available
 */


#include <stdio.h>
#include <omp.h>
#include <list>

void new_thread(std::list<int>::iterator& it);
void end_result(const std::list<int>& ls);

int main(int argc, char** argv)
{
	std::list<int> ls;
	for (int i=-1; i<10; i++) ls.push_back (i); // from -1, later += 1

#pragma omp parallel
	{
#pragma omp single
		{
			for(std::list<int>::iterator it = ls.begin(); it!=ls.end(); ++it)
			{
#pragma omp task
				{
					new_thread (it);
				}/* end of task */
			}
		}/* end of single */
	}/* end of parallel */


	end_result (ls);

	return 0;
}

void new_thread (std::list<int>::iterator& it)
{
	*it += 1;
	printf ("%d %d\n", omp_get_thread_num (), *it);
}

void end_result(const std::list<int>& ls)
{
	for (std::list<int>::const_iterator it = ls.begin(); it != ls.end(); ++it)
		printf ("%d ", *it);
	printf("\n");
}
