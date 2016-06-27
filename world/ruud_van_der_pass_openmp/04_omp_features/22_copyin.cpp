/*  The copyin clause is used to initialize threadprivate data upon entry
    to a parallel region.
    The value of the threadprivate variable in the master thread is copied
    to the threadprivate variable of each other team member.
*/


#include <stdio.h>
#include <omp.h>


int i,j;
#pragma omp threadprivate(i,j)

void printvar()
{
	printf ("thread= %d i= %d j= %d\n", omp_get_thread_num(), i, j);
}

void func()
{
	i = omp_get_thread_num ();
	j = 100 + i;

#pragma omp parallel copyin(i,j)
	{
		printvar ();
	}/* end of parallel */
}

int main(int argc, char** argv)
{
	i= -1, j= -1;

	func();

	return 0;
}
