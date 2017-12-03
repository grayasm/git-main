/* Cap.4 Functions and Program Structure, pag.84

   The register declaration can be applied to automatic variables and
   formal parameters to a function.
*/

#include <stdio.h>

void function(register unsigned m, register long n)
{
    register int i;

    i = m * n;
    printf("value=%d\n", i);
}

main()
{
    function(2, 2);
}
