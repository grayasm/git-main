/* Cap.2 Types, Operators and Expressions pag.40

   External and static variables are initialized to zero by default.
   Automatic variables for which there is no explicit initializer have undefined
   (i.e. garbage) values.
*/


#include <stdio.h>

static int v0;
int v1;

main()
{
    int v2;
    printf("default static value=%d\n", v0);
    printf("default global value=%d\n", v1);
    printf("default local  value=%d\n", v2);
}
