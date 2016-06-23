/* Writing the first OpenMP program.
   Multiplication of matrix B(m,n) with vector c(n).
   Book example.
*/

#include <stdio.h>
#include <stdlib.h>

void mxv(int m, int n,
         double * restrict a,
         double * restrict b,
         double * restrict c);

int main(int argc, char* argv[])
{
	double *a,*b,*c;
	int i,j,m,n;

	printf("Please give m and n: ");
	scanf("%d %d", &m, &n);

	if ((a=(double *)malloc(m*sizeof(double))) == NULL)
		perror("memory allocation for a");
	if ((b=(double *)malloc(m*n*sizeof(double))) == NULL)
		perror("memory allocation for b");
	if ((c=(double *)malloc(n*sizeof(double))) == NULL)
		perror("memory allocation for c");

	printf("Initializing matrix B and vector c\n");
	for (j=0; j<n; j++)
		c[j] = 2.0;
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
			b[i*n+j] = i;

	print_mat (m, n, b);
	print_vec (n, c);

	printf("Executing mxv function for m = %d n = %d\n", m, n);
	(void)mxv(m,n,a,b,c);

	print_vec (m, a);

	free(a); free(b);free(c);
	return(0);
}

void mxv(int m, int n,
         double * restrict a,
         double * restrict b,
         double * restrict c)
{
	int i,j;

	for (i=0; i<m; i++)
	{
		a[i] = 0.0;
		for (j=0; j<n; j++)
			a[i] += b[i*n+j]*c[j];
	}
}

void print_mat(int m, int n, double * restrict b)
{
	int i,j;

	printf("Matrix (%d,%d) = \n", m, n);
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
			printf("\t%d", b[i*n+j]);
		printf("\n");
	}
}

void print_vec(int m, double * restric c)
{
	int i;

	printf("Vector (%d) = \n", m);
	for (i=0; i<m; i++)
		printf("\t%d\n", c[m]);
}
