/* using single construct to initialize a data structure before using it. */

#include <stdio.h>
#include <vector>
#include <omp.h>


int main(int argc, char** argv)
{
	const int MAX= 5;
	std::vector<int> vec;

#pragma omp parallel
	{
#pragma omp single
		{
			vec.resize(MAX, -1);
			for (size_t i=0; i<vec.size(); ++i) vec[i] = i+100;
			printf("omp single th= %d\n", omp_get_thread_num ());

		}/*End of single block (barrier). */

#pragma omp for
		for (size_t j=0; j<vec.size(); ++j)
			printf("omp for    th= %d val= %d\n", omp_get_thread_num(), vec[j]);

	}/*End of parallel region. */

	return 0;
}
