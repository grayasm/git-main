/* Cap.5 Pointers and Arrays, pag.107

   Exercise 5-5: Write versions of the library functions strncpy, strncat and
                 strncmp which operate on at most the first n characters of
                 their argument strings. For example, strncpy(s,t,n) copies
                 at most n characters of t to s.
                 Full descriptions are in Appendix B.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strncpy_(char *s, const char *t, int n);
int strncmp_(char *s, const char *t, int n);
void strcat_(char *s, const char *t, int n);


main()
{
    char s[100] = "1234567890";
    char t[100] = "987654321";

    strncpy_(s, t, strlen(t));
}


/* strncpy:  copy at most n characters of t to s */
void strncpy_(char *s, const char *t, int n)
{
    while (*t && n-- > 0)
        *s++ = *t++;
    *s = '\0';
}


/* strncmp:  compare at most n characters of s and t, return <0 if s<t,
             0 if s==t, >0 if s>t */
int strncmp_(char *s, const char *t, int n)
{
    for (; *s == *t && n-- > 0; s++, t++)
        if (*s == '\0' || n == 0)
            return 0;
    return *s - *t;
}

/* strcat:  concatenate at most n characters of t to the end of s; s
            must be big enough */
void strcat_(char *s, const char *t, int n)
{
    while (*s)              /* find end of s */
        s++;
    while (*t && n-- > 0)   /* copy at most n characters of t */
        *s++ = *t++;
    *s = '\0';
}
