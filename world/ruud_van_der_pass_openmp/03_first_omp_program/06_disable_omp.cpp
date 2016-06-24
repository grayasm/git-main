/* Conditional compilation:
   without -fopenmp           compile option     flag
   without -D_OPENMP=201107   compile definition flag
*/

#include <stdio.h>
#include <vector>
// /usr/lib/gcc/x86_64-redhat-linux/4.8.2/include/omp.h


/* The advised method is this: */
#if defined (_OPENMP)
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif



int main(int argc, char* argv[])
{
	int i, TID;
	const int SZ=10;
	std::vector<double> v(SZ, 0.);


#pragma omp parallel for shared(v) private(i,TID)  // ignored by compiler
	for (i=0; i<SZ; i++)
	{
		v[i] = i*100;
		TID = omp_get_thread_num ();  // always the main thread = 0
		printf("TID=%d\n", TID);
	}
/* end of parallel for */


	return 0;
}
