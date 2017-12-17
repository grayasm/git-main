/* Cap.2 Types, Operators and Expressions, pag.42

   A naive implementation of the function atoi, which converts a string
   of digits into its numeric equivalent.
*/

#include <stdio.h>

/* atoi: convert s to integer */
int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = n * 10 + s[i] - '0';
    return n;
}

main()
{
    printf ("atoi(7)  = %d\n", atoi("7"));
    printf ("atoi(18) = %d\n", atoi("18"));
    printf ("atoi(89) = %d\n", atoi("89"));
    printf ("atoi(380)= %d\n", atoi("380"));
}
