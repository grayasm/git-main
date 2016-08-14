#include <iostream>
#include <omp.h>ssss

using namespace std;
int main(int argc, char** argv)
{
	int i;
	const int N=25;

#pragma opm parallel
	{
#pragma omp for
		for(i=0; i<N; i++)
		{
#pragma omp atomic
			cout << omp_get_thread_num() << " "
		}// end of for
	}// end of parallel
	return 0;
}
