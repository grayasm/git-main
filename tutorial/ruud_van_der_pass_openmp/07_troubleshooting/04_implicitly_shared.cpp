/*  Cap7. pag 249 Fig 7.5 - Example of a loop variable that is implicitly shared

    Loop variable i is private by default, but this is not the case for j: it is
    shared by default. This results in undefined runtime behavior.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int n = 10, m = 10;
	int i,j, a[n][m];

#pragma omp parallel for
	for (i=0; i<n; i++)
	{
		for (j=0; j<m; j++)
		{
			a[i][j] = i * j;
		}
	}/* end of parallel */


	int sum = 0;
	for (i=0; i<n; i++)
		for (j=0; j<m; j++)
			sum += a[i][j];

	printf ("sum = %d, correct is %d\n", sum, 2025);

	return 0;
}
