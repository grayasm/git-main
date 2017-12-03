/* Cap.4 Functions and Program Structure, pag.87

   4.10 Recursion
   Consider printing a number as a character string. The digits are generated
   in the wrong order: low-order digits are available before high-order digits,
   but they have to be printed the other way around.
*/

#include <stdio.h>

/* printd: print n in decimal */
void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n/10)
        printd(n / 10);
    putchar(n % 10 + '0');
}


main()
{
    printd(123);
}
