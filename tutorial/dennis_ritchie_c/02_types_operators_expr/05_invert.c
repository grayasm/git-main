/* Cap.2 Types, Operators and Expressions, pag.49

   Exercise 2-7.  Write a function invert(x,p,n) that returns x with the n bits
   that begin at position p inverted (i.e. 1 changed into 0 and vice versa)
   leaving the other unchanged.
*/

#include <stdio.h>

int invert(int x, int p, int n)
{
    int m; // mask

    m = ~(~0 << n) << p;
    return x ^ m;
}

main()
{
    int x, p, n;

    x = 3451;
    p = 2;
    n = 6;

    printf ("invert(%d, %d, %d) = %d\n", x, p, n, invert(x,p,n));
}
/*
invert(3451, 2, 6) = 3463

first our number x = 3451   as binary = 1101 0111 1011   <-- x
~0 << n to begin the mask   as binary = 1111 1100 0000
~(~0 << n) to flip the mask,as binary = 0000 0011 1111
now again << p to finalize  as binary = 0000 1111 1100   <-- m
and toggle the bits x^m     as binary = 1101 1000 0111
                                             ^^^^ ^^
xor ^ with 1 toggles the bit
 */
