/* Cap.2 Types, Operators and Expressions, pag.49

   Exercise 2-8: Write a function rightrot(x,n) that returns the value of the
                 integer x rotated to the right by n bit positions.
*/

#include <stdio.h>

int rightrot(unsigned int x, int n)
{
    while (n-- > 0)
    {
        if (x & 1)
            x = (x >> 1) | ~(~0U >> 1);
        else
            x = x >> 1;
    }
    return x;
}


main()
{
    printf ("rightrot(%d, %d)=%d\n", 119, 4, rightrot(119, 4));
}
/*
rightrot(119, 4)=1879048199
0000 0000 0000 0000 0000 0000 0111 0111 =        119
0111 0000 0000 0000 0000 0000 0000 0111 = 1879048199
*/
