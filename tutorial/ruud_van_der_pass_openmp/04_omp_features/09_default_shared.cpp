/*  default(shared) assigns the shared attribute to all variables referenced
    in the construct.

    For those not shared, private(list ) must be specified.
*/

#include <stdio.h>
#include <omp.h>



int main(int argc, char** argv)
{
	const int MAX=13;
	int t, a[MAX];
	for (t=0; t<MAX; t++) a[t]=-1;


#pragma omp parallel default(shared) private(t)
	{
		t = omp_get_thread_num ();
		if ( t < MAX)
			a[t] = t;

	} /* end of parallel region */


	for (t=0; t<MAX; t++)
		printf("end of parallel a[%d]= %d\n", t, a[t]);

	return 0;
}
