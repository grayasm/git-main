/* 4.4.1 Loop Construct
         The syntax is:
         #pragma omp for [clause [[,] clause] ..]
             for-loop

   For loop is of the form:
   for (init-expr; var relop b; incr-expr)

 - the iterations can be counted;
 - a counter is used for incrementing/decrementing
 - an upper or lower bound is specified

  Here an attempt to use for-loop with std::set<>
  Cannot be used effectively with std::set which has bidirectional iterator.
  Incrementing set.begin() in each thread to match i is totally ineffective.
*/

#include <stdio.h>
#include <set>
#include <omp.h>



int main(int argc, char** argv)
{
	int i, j;
	const int MAX = 5;
	std::set<int> st;
	for(i=0; i<MAX; ++i) st.insert(i+100);


#pragma omp parallel shared(st) private(i,j)
	{
		#pragma omp for
		for(i = 0; i<st.size(); ++i) // cannot use iterators
		{
			std::set<int>::iterator it = st.begin();
			// increment bidirectional iterator - NO GO!
			for (j=0; j<i; ++j)
				it++;


			printf("thread %d set's node %d\n", omp_get_thread_num(), *it);
		}

		// how many threads are in the parallel region?
		printf("thread %d\n", omp_get_thread_num());
	}

	return 0;
}
