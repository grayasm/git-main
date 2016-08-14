#include <iostream>
#include <omp.h>

using namespace std;
int main(int argc, char** argv)
{
    const int N=25;
    int i;

#pragma omp parallel for private(i)
    for(i=0; i<N; i++)
    {
#pragma omp critical
	    {
		    cout << "i= " << i << " thid= " << omp_get_thread_num() << endl;
	    }
    }// end of parallel region
    cout << endl;

    return 0;
}
