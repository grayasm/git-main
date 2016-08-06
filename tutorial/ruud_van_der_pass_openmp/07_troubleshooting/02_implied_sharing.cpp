/*  Cap 7. pag.247 - 7.2.2 Default Data-Sharing Attributes

    By default, variable Xshared is shared.
    The assignment to Xshared causes a data race: if multiple threads are used,
    they simultaneously store a different value in the same variable.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	int Xshared;

#pragma omp parallel
	{
		int Xlocal = omp_get_thread_num ();
		Xshared = omp_get_thread_num (); /*-- Data race --*/

		printf ("Xlocal = %d Xshared = %d\n", Xlocal, Xshared);
	}/* end of parallel */

	return 0;
}
