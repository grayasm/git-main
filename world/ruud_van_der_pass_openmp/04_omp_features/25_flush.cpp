/*  All modifications to shared variables are written back to main memory and
    are thus available to all threads, at synchronization points in the program.
    Between these synchronization points, threads are permitted to have new
    values for shared variables stored in their local memory rather than in
    the global shared memory.

    This approach, called a relaxed consistency model, makes it easier for the
    system to offer good program performance.

    But sometimes this is not enough. Sometimes updated values of shared values
    must become visible to other threads in-between synchronization points.
    The OpenMP API provides the flush directive to make this possible.
    The purpose of the flush directive is to make a thread’s temporary view of
    shared data consistent with the values in memory.

    syntax: #pragma omp flush [(list)]
*/


#include <stdio.h>
#include <omp.h>


void read(int*);
void proc(int*);

int main(int argc, char** argv)
{
    int data, flag=0;

#pragma omp parallel sections num_threads(2)
    {

#pragma omp section
        {
            printf ("thread %d: ", omp_get_thread_num ());
            read (&data);

#pragma omp flush (data)
            flag = 1;
#pragma omp flush (flag)
        }/* end of section */


#pragma omp section
        {
            while (!flag)
            {
#pragma omp flush (flag)
            }

#pragma omp flush (data)

            printf ("thread %d: ", omp_get_thread_num ());
            proc (&data);
            printf ("data= %d\n", data);
        }/* end of section */

    }/* end of sections */

    return 0;
}


void read(int* data)
{
    * data = 1;
    printf("read data=%d\n", *data);
}

void proc(int* data)
{
    (*data)++;
    printf("proc data=%d\n", *data);
}
