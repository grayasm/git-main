/* 4.4.1 Loop Construct
         The syntax is:
         #pragma omp for [clause [[,] clause] ..]
             for-loop

   For loop is of the form:
   for (init-expr; var relop b; incr-expr)

 - the iterations can be counted;
 - a counter is used for incrementing/decrementing
 - an upper or lower bound is specified

 Obviously it cannot be used with a list.
 - the iterators are not random-access
 - even if the loop if faked: for(size_t i=0; i<lst.size(); ++i){ cb++; ..}
   the icrementation of lst.begin() must be sequential
 - the only way it works is to iterate over i=0; i<lst.size() and inside
   each thread to start incrementing lst.begin() up to i position.
*/

#include <stdio.h>
#include <list>
#include <omp.h>



int main(int argc, char** argv)
{
	std::list<int> lst;
	for(int i=0; i<3; ++i) lst.push_back(i);
	std::list<int>::const_iterator cb, ce;



#pragma omp parallel
	{
		#pragma omp for
		for(cb = lst.begin(); cb != lst.end(); ++cb) // invalid
		{
			printf("thread %d list's node %d\n", omp_get_thread_num(), *cb);
		}
	}

	return 0;
}
