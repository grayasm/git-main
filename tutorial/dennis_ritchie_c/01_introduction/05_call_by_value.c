/* Cap.1 A Tutorial Introduction, pag.27

   In C all function arguments are passed "by value"
*/

#include <stdio.h>

/* power: raise base to n-th power; n>=0; version 2 */
int power(int base, int n)
{
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}

int main()
{
    int i;

    for (i = 0; i < 10; ++i)
        printf ("%d %d %d\n", i, power(2, i), power(-3, i));

    return 0;
}
/*
0 1 1
1 2 -3
2 4 9
3 8 -27
4 16 81
5 32 -243
6 64 729
7 128 -2187
8 256 6561
9 512 -19683
*/
