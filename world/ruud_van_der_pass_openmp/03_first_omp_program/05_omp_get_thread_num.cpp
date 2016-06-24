/* Conditional compilation with _OPENMP */

#include <stdio.h>
#include <vector>


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


#pragma omp parallel for shared(v) private(i,TID)
	for (i=0; i<SZ; i++)
	{
		v[i] = i*100;
		TID = omp_get_thread_num (); // current thread number
		printf("TID=%d\n", TID);
	}
/* end of parallel for */


	return 0;
}
