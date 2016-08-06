/* pag 54, Fig 4.1  syntax of the parallel construct

   #pragma omp parallel [clause[[,] clause]. . . ]
       structured block
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	int i=0, MAX=10, r=0;

#pragma omp parallel
	while(i++ < MAX)
	{
		printf("omp_get_thread_num=%d\n", omp_get_thread_num ());
		r += i; // r= n(n+1)/2 = 9*10/2 = 90/2 = 45
	}
/* End of omp parallel */

	if (r != 45) printf("Error, r=%d\n", r);
	else         printf("OK, r=%d\n", r);

	return 0;
}
