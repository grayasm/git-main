/* 4.4.1 Loop Construct
         The syntax is:
         #pragma omp for [clause [[,] clause] ..]
             for-loop

   For loop is of the form:
   for (init-expr; var relop b; incr-expr)

 - the iterations can be counted;
 - a counter is used for incrementing/decrementing
 - an upper or lower bound is specified

 Here an attempt to use for-loop with std::map<>
 Pretty bad, cannot use iterators and have to access elements by index (mp[i]).
 Map operations insert,search are 0(log N)
*/

#include <stdio.h>
#include <map>
#include <omp.h>



int main(int argc, char** argv)
{
	int i = 0;
	const int MAX = 5;
	std::map<int, int> mp;
	for(i=0; i<MAX; ++i) mp.insert(std::pair<int,int>(i,i));


#pragma omp parallel
	{
		#pragma omp for
		for(i = 0; i<mp.size(); ++i)
		{
			printf("thread %d map's node %d\n", omp_get_thread_num(), mp[i]);
		}

		// how many threads are in the parallel region?
		printf("thread %d\n", omp_get_thread_num());
	}

	return 0;
}
