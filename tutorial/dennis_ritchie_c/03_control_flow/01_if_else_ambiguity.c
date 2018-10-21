/* Cap.3 Control Flow, pag.56

   Because the else part of an if-else is optional, there is an ambiguity
   when an else is omitted from a nested if sequence. This is resolved by
   associating the else with the closest previous else-less if.
 */

#include <stdio.h>

void main()
{
    int x = 1, y = 2, z = -1;
    int a;

    if (x > 0)
        if (y > 0)
            if (z > 0)
                a = 1;
            else
                a = 2;
        else
            a = 3;
    else
        a = 4;

    printf("a=%d\n", a);
}
/*
a=2
*/
