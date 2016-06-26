/*  If default(none) is specified, the programmer is forced to specify a
    data-sharing attribute for each variable in the construct.

    Although variables with a predetermined data-sharing attribute need not
    be listed in one of the clauses, we strongly recommend that the attribute
    be explicitly specified for all variables in the construct.

    Uncomment data-sharing attribute to compile.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int MAX=13;
	int t, a[MAX];
	for (t=0; t<MAX; t++) a[t]=-1;


#pragma omp parallel default(none) // shared(a) private(t)
	{
		t = omp_get_thread_num ();
		if ( t < MAX)
			a[t] = t;

	} /* end of parallel region */


	for (t=0; t<MAX; t++)
		printf("end of parallel a[%d]= %d\n", t, a[t]);

	return 0;
}
