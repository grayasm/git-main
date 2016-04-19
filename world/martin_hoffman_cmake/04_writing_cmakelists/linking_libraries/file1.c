#include <stdio.h>
#include <math.h>

//include_directories (dir1)
#include "header1.h"

//target_include_directories(dir2)
#include "header2.h"


int main(int argc, char** argv)
{
	printf ("\nMessage from %s", __FILE__);
	printf ("\n<math.h> M_PI= %f", M_PI);
	printf ("\nsin(45)= %.2f\n\n", sin (45.0 * M_PI/180.0));

	printf ("\nfrom CMake add_definitions:");
#ifdef NDEBUG
	printf ("\nNDEBUG: OK");
#else
	printf ("\nNDEBUG: NOT-OK");
#endif

#ifdef UNICODE
	printf ("\nUNICODE: OK");
#else
	printf ("\nUNICODE: NOT-OK");
#endif

#ifdef WCHAR
	printf ("\nWCHAR: OK");
#else
	printf ("\nWCHAR: NOT-OK");
#endif

	printf ("\nfrom CMake target_compile_definitions:");
#ifdef TARGET
	printf ("\nTARGET: OK");
#else
	printf ("\nTARGET: NOT-OK");
#endif

#ifdef PUBLIC
	printf ("\nPUBLIC: OK");
#else
	printf ("\nPUBLIC: NOT-OK");
#endif

#ifdef INTERFACE
	printf ("\nINTERFACE: why is it defined?");
#else
	printf ("\nINTERFACE: undefined by intent: OK");
#endif

	printf ("\nCMake include_directories(dir1)");
	header1();


	printf ("\nCMake target_include_directories(app PUBLIC dir2)");
	header2();


	printf("\n\n");
	return 0;
}
