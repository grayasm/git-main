/* Cap.1 A Tutorial Introduction, pag.33

   Write an extern declaration in the function; the declaration is the same
   as before except for the added keyword extern.
 */

#include <stdio.h>

#define MAXLINE 10
char s[MAXLINE];
int i = 0, c;

main()
{
    extern int i, c;
    extern char s[MAXLINE];

    while ((c = getchar()) != EOF)
    {
        if (i + 1 < MAXLINE)
            s[i++] = (char)c;
        else
            s[i] = '\0', printf("%s", s), i = 0, s[i++] = (char)c;
    }
    if (i > 0)
        s[++i] = 0, printf("%s", s), i = 0;
}
