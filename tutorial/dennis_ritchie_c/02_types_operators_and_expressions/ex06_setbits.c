/* Cap.2 Types, Operators and Expressions, pag. 49

   Exercise 2-6: Write a function setbits(x,p,n,y) that returns x with the n
                 bits that begin at position p set to the rightmost n bits of y
                 leaving the other bits unchanged.
*/

#include <stdio.h>
#include <stdlib.h>

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);
unsigned setbits2(unsigned x, unsigned p, unsigned n, unsigned y);

int main(void)
{
    /*
      p = 4
      n = 3
      y = 0000 0011    =3    <-take these 3 bits
                ^^^
      x = 1111 0101    =245  <-set them at pos 4
           ^^^
      s = 1011 0101    =181  <-leave the others unchanged
           ^^^
     */
    printf("check: 181=%u\n", setbits(245, 4, 3, 3));
    printf("check: 181=%u\n", setbits2(245, 4, 3, 3));

    return EXIT_SUCCESS;
}


unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
    unsigned a,b,c,d,m;
    unsigned f,g,i,j;

    
    a = ~(~(unsigned)0 << n); /* 0000 0111 */
    b = ~a;                   /* 1111 1000 */
    
    c = (a << p);             /* 0111 0000 */
    d = ~(~b << p);           /* 1000 1111 */

    m = y & a;                /* 0000 0011 */
    m = (m << p);             /* 0011 0000 */

    f = x & c;                /* 0111 0000 */
    g = x & d;                /* 1000 0101 */

    i = f & m;                /* 0011 0000 */
    j = i | g;                /* 1011 0101 */

    return j;
}

unsigned setbits2(unsigned x, unsigned p, unsigned n, unsigned y)
{
    unsigned m1,m2,m3;
    m1 = y & ~(~(unsigned)0 << n);        /* 0000 0011 */
    m1 = (m1 << p);                       /* 0011 0000 */
    m2 = ~(~(unsigned)0 << n) << p;       /* 0111 0000 */
    m3 = ~m2;                             /* 1000 1111 */
    return ((x & m1) | (x & m3));         /* 1011 0101 */
}
