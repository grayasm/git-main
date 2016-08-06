/* Using shared clause with parallel for.
   Syntax:   shared(list)
   The variable in the parallel section is shared among the team of threads.
   The concurent access to the shared variables happens non-atomic.
   There is no locking when writing to a shared variable.
*/
#include <stdio.h>
#include <vector>
#include <omp.h>



int main(int argc, char** argv)
{
	std::vector<int> a(5, 0);
	size_t i;

#pragma omp parallel for shared(a)
	for (i=0; i<a.size(); i++)
	{
		a[i] += omp_get_thread_num ();
		printf("thread %d over i= %d\n", omp_get_thread_num(), i);

	} /* End of parallel region. */


	for (i=0; i<a.size(); ++i)
		printf("a[%d]= %d\n", i, a[i]);
	return 0;
}
