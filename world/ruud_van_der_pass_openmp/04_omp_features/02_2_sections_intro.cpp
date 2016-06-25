/*  The sections contruct distributes each thread to a section.
    The syntax:

    #pragma omp parallel ...
    {
    #pragma omp sections [clause [[,] clause ...]]
      {
      [#pragma omp section]
        structured block

      [#pragma omp section]
        structured block
      }
    }
*/

#include <stdio.h>
#include <omp.h>


void funcA();
void funcB();

int main(int argc, char** argv)
{

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            funcA();

#pragma omp section
            funcB();

        } /* End of sections block. */

        printf("omp parallel, thread %d\n", omp_get_thread_num ());
    }
    /* End of parallel region. */

    return 0;
}

void funcA()
{
    printf("funcA() thread %d\n", omp_get_thread_num ());
}

void funcB()
{
    printf("funcB() thread %d\n", omp_get_thread_num ());
}
