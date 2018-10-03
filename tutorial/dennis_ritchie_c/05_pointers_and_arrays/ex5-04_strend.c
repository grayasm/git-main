/* Cap.5 Pointers and Arrays, pag.107

   Exercise 5-4: Write a function strend(s,t) which returns 1 if the string t
                 occurs at the end of the string s, and zero otherwise.
*/

#include <stdio.h>
#include <stdlib.h>


/* strend:  returns 1 if the string t occurs at the end of the string s,
   and zero otherwise */
int strend(const char *s, const char *t)
{
    int ls, lt;

    for (ls = 0; *(s+ls); ++ls)     /* find length of s */
        ;
    for (lt = 0; *(t+lt); ++lt)     /* find length of t */
        ;
    if (ls >= lt) {         /* check if t can fit in s */
        s += ls - lt;       /* point s to where t should start */
        while (*s++ == *t++)
            if (!*s)        /* we found end of s and therefore t */
                return 1;   /* so return 1 */
    }
    return 0;
}

int main(void)
{
    char s[100] = "abcdef\0xyz";
    char t[100] = "def\0klm";
    printf("%d\n", strend(s, t));
    return EXIT_SUCCESS;
}
