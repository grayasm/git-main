/*  Cap.7 pag. 244 - 7.2.1 Data Race Conditions

    A data race condition exists when two threads may concurrently access the
    same shared variable between synchronization points, without holding any
    common locks and with at least one thread modifying the variable.
    The order of these accesses is nondeterministic. The thread reading the
    value might get the old value or the updated one, or some other erroneous
    value if the update requires more than one store operation. This usually
    leads to indeterministic behavior, with the program producing different
    results from run to run.

    Data race conditions depends on factors like:
    - Load on the system. The relative timing between the threads matters.
    - Input data set. This might, for instance, lead to some load imbalance
    that affects the speed with which individual threads reach the incorrectly
    parallelized code.
    - Number of threads used. In some cases the problem shows up only for a
    specific number of threads.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int n=10;
	int i, a[n], b[n];
	for (i=0; i<n; i++)
	{
		a[i] = i - 1;
		b[i] = i;
	}

#pragma omp parallel for shared(a,b) private(i)
	for (i=0; i<n-1; i++)
	{
		a[i] = a[i + 1] + b[i];
	}/* end of parallel */


	for (i=0; i<n-1; i++)
		printf ("a[%d] = %d , correct is= %d\n", i, a[i], (i + i));

	return 0;
}
