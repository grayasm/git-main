/* Synchronization construct: atomic

   syntax: #pragma omp atomic
               statement

   The atomic construct, which also enables multiple threads to update shared
   data without interference, can be an efficient alternative to the critical
   region.
   In contrast to other constructs, it is applied only to the (single)
   assignment statement that immediately follows it;

   The atomic construct may only be used together with an expression statement
   in C/C++, which essentially means that it applies a simple, binary operation
   such as an increment or decrement to the value on the left-hand side.

   The supported operations are: +, *, -, /, &, ^, |, <<, >>
 */



#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    const int MAX=5;
    int i, a[MAX], sum=0;


#pragma omp parallel for shared(a, sum) private(i)
    for (i=0; i<MAX; i++)
    {
	    a[i] = i;

#pragma omp atomic
	    sum += a[i];

    }

    printf ("sum= %d\n", sum); // sum(0:4)=4*5/2 = 20/2 = 10;
    if (sum == 10) printf("OK\n");
    else           printf("Error\n");

    return 0;
}
