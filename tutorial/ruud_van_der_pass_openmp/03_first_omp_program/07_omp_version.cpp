/* Print the version of current OpenMP Implementation.
 */

#include <stdio.h>
#include <omp.h>


struct OmpVersion
{
	const char* date;
	const char* version;
	int         ival;
};


int main(int argc, char** argv)
{
	// Release History
	// https://computing.llnl.gov/tutorials/openMP/
	const int MAX=10;
	OmpVersion ver[MAX] = { {"Oct 1997", "Fortran 1.0", 199710},
	                        {"Oct 1998", "C/C++ 1.0",   199810},
	                        {"Nov 1999", "Fortran 1.1", 199911},
	                        {"Nov 2000", "Fortran 2.0", 200011},
	                        {"Mar 2002", "C/C++ 2.0",   200203},
	                        {"May 2005", "OpenMP 2.5",  200505},
	                        {"May 2008", "OpenMP 3.0",  200805},
	                        {"Jul 2011", "OpenMP 3.1",  201107},
	                        {"Jul 2013", "OpenMP 4.0",  201307},
	                        {"Nov 2015", "OpenMP 4.5",  201511} };

#if defined(_OPENMP)
	for (int i=0; i<MAX; i++)
		if (ver[i].ival == _OPENMP)
		{
			printf ("OpenMP Release: %s - %s (%d)\n",
			        ver[i].date, ver[i].version, ver[i].ival);
			return 0;
		}

	printf ("OpenMP Release: Unknown for _OPENMP=%d\n", _OPENMP);
#else
	printf ("OpenMP Release: Unknown - _OPENMP= (undefined)\n");
#endif

	return 0;
}
