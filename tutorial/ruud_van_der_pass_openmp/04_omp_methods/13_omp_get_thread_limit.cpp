/*  int omp_get_thread_limit(void);

    Return the maximum number of threads of the program.
*/


#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    int tlim;

    tlim = omp_get_thread_limit ();
    printf ("main    = %d\n", tlim);

#pragma omp parallel num_threads(6)
#pragma omp master
    {
        tlim = omp_get_thread_limit ();
        printf ("parallel= %d\n", tlim);
    }/* end of parallel */


    return 0;
}

/*
$>  ./13_omp_get_thread_limit
main    = 2147483647
parallel= 2147483647
*/
