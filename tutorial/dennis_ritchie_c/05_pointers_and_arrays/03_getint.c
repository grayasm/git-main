/* Cap.5 Pointers and Arrays, pag.97

   As an example consider a function getint that performs free-format input
   conversion by breaking a stream of characters into integer values, one
   integer per call.
*/

#include <stdio.h>
#include <ctype.h>



#define BUFSIZE 100
char buf[BUFSIZE];    /* buf for ungetch */
int bufp = 0;         /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)   /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters \n");
    else
        buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while(isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);                /* it's not a member */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 5
main()
{
    int n, array[SIZE], getint(int *);

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        printf("n=%d array[%d]=%d\n", n, n, array[n]);
}
