/* Cap.3 Control Flow, pag. 61

   Here is another version of atoi for converting a string to its numeric
   equivalent. This one is slightly more general than the one in Cap.2
   it copes with optional leading white space and an optional + or - sign.
*/

#include <stdio.h>
#include <ctype.h>

/* atoi: convert s to integer; version 2 */
int atoi (char s[])
{
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++)  /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')  /* skip sign */
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

main()
{
    char s[]="-1001";
    printf ("atoi(%s) = %d\n", s, atoi(s));
}

/*
  atoi(-1001) = -1001
*/
