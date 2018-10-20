/* Cap.2 Types, Operators and Expressions, pag.49

   Note that x & ~077 is independent of word length, and is thus preferable to,
   for example, x & 0177700, which assumes that x is a 16-bit quantity.

   Print the bits of an integer (My example).
 */

#include <stdio.h>

void printbits(unsigned int x)
{
    unsigned int m = ~(~(unsigned)0 >> 1);

    while (x) {

        if ((x & m) == m)
            printf("%d", 1);
        else
            printf("%d", 0);

        x <<= 1;
    }
}


int main()
{
    unsigned int x = 153; /* 1001 1001 */

    printf("x = %d(10) = ", x);
    printbits(x);
    printf("(2)\n");

    return 0;
}

/*
x = 153(10) = 00000000000000000000000010011001(2)
*/
