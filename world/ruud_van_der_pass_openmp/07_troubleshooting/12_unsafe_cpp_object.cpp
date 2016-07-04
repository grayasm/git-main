/* Cap7. pag 259
   Fig. 7.17 Example of unsafe use of a shared C++ object.

   Another source of hidden side effects is shared class objects and methods
   in C++. When class objects with methods defined on them are used as shared
   variables within OpenMP parallel regions, race conditions can result.

   When executed on 2 threads, the expected result is 20.
   However, data race conditions may yield indeterministic results.
*/

#include <stdio.h>
#include <omp.h>


class anInt
{
public:
	int x;
	anInt(int i=0){ x = i; }
	void addInt (int y) { x = x + y; }
}; // class


int main(int argc, char** argv)
{
	anInt a(10);

#pragma omp parallel num_threads(10)
	{
		a.addInt (5);
	}/* end of parallel */

	printf ("anInt.x=%d, correct is=%d\n", a.x, 10+5*10);
	return 0;
}
