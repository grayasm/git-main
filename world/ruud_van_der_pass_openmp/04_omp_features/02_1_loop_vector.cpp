/* 4.4.1 Loop Construct
         The syntax is:
         #pragma omp for [clause [[,] clause] ..]
             for-loop

   For loop is of the form:
   for (init-expr; var relop b; incr-expr)

 - the iterations can be counted;
 - a counter is used for incrementing/decrementing
 - an upper or lower bound is specified

 An exercise, using for-loop with a std::vector<>
*/

#include <stdio.h>
#include <vector>
#include <omp.h>



int main(int argc, char** argv)
{
	int i = 0;
	const int MAX = 5;
	std::vector<int> vec(MAX, 0);
	for(i=0; i<MAX; ++i) vec[i]= i + 100;


#pragma omp parallel shared(vec) private(i)
	{
		#pragma omp for
		for(i=0; i < vec.size(); i++)
		{
			printf("thread %d vector[%d]=%d\n", omp_get_thread_num(), i,vec[i]);
		}

		// how many threads are in the parallel region?
		printf("thread %d\n", omp_get_thread_num());
	}

	return 0;
}
