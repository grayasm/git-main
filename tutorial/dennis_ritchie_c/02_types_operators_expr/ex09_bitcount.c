/* Cap.2 Types, Operators and Expressions, pag.51

   Exercise 2-9. In a two's complement number system, x &= (x - 1) deletes the
                 rightmost 1-bit in x. Explain why.
                 Use this observation to write a faster version of bitcount.
*/

#include <stdio.h>

int bitcount(unsigned int x)
{
    int b;

/*  for (b = 0; x != 0; x = x >> 1)
        if (x & 01)
            b++;
*/
    for (b = 0; x != 0; x &= (x-1))
            b++;
    return b;
}

main()
{
    printf ("bitcount(%d) returns %d bits of 1\n", 119, bitcount(119));
}


/*
bitcount(119) returns 6 bits of 1
*/
