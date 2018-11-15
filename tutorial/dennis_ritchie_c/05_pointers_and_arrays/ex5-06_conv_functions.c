/* Cap.5 Pointers and Arrays, pag.107

   Exercise 5-6: Rewrite appropriate programs from earlier chapters and
                 exercises with pointers instead of array indexing. Good
                 possibilities include getline (Chapters 1 and 4), atoi, itoa
                 and their variants (Chapters 2, 3 and 4), reverse (Chapter 3)
                 and strindex and getop (Chapter 4).
*/

#include <stdio.h>
#include <stdlib.h>     /* abs() */
#include <string.h>
#include <ctype.h>

int strindex(const char *s, const char *t);
void reverse(char *s);
void itoa_(int n, char *s);
int atoi_(const char *s);
int getop(char *s);
int getline_(char *s, int lim);

main()
{
    char s[] = "0123456789";
    reverse(s);
    printf("reverse(0123456789)=%s\n", s);
}


/* strindex:  return index of t in s, -1 if none */
int strindex(const char *s, const char *t)
{
    const char *i, *j, *k;

    for (i = s; *i != '\0'; i++) {      /* for each character in s */
        j = i, k = t;
        while(*k != '\0' && *j++ == *k++);
        if (k-t > 0 && *k == '\0')      /* if it is the start of t */
            return i-s;                 /* return its index */
    }
    return -1;                          /* t was not found return -1 */
}

/* reverse:  reverse string s in place */
void reverse(char *s)
{
    char tmp, *p;
    p = s + strlen(s) - 1;
    while (p > s) {
        tmp = *s;
        *s++ = *p;
        *p-- = tmp;
    }
}

/* itoa_:  convert n to characters in s */
void itoa_(int n, char *s)
{
    int sign;
    char *p;

    p = s;
    sign = n;
    do {        /* generate digits in reverse order */
        *p++ = abs(n % 10) + '0';   /* get next digit */
    } while (n /= 10);              /* delete it */
    if (sign < 0)
        *p++ = '-';
    *p = '\0';
    reverse(s);
}


#define NUMBER '0'  /* signal that a number was found */
int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char *s)
{
    char c;

    while ((*s = c = getch()) == ' ' || c == '\t');
    *++s = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    --s;                /* remove the \0 */
    if (isdigit(c))     /* collect intiger part */
        while (isdigit(*++s = c = getch()));
    if (c == '.')       /* collect fraction part */
        while (isdigit(*++s = c = getch()));
    *s = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}


#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getline_:  get line into s, return length */
int getline_(char *s, int lim)
{
    char c, *p;

    p = s;  /* point p to s */
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - p;
}

/* atoi_:  convert string s to integer */
int atoi_(const char *s)
{
    int n, sign;

    while (isspace(*s))
        s++;                        /* skip whitespace */
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')     /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s -'0');
    return sign * n;
}
