/* Cap.5 Pointers and Arrays, pag.107

   Exercise 5-3: Write a pointer version of the function strcat that we showed
                 in Chapter 2: strcat(s,t) copies the string t to the end of s.
*/

#include <stdio.h>
#include <stdlib.h>

/* strcat:  concatenate t to end of s; s must be big enough */
void strcat_(char *s, const char *t)
{
    while (*s)      /* find end of s */
        s++;
    while (*t)      /* copy t */
        *s++ = *t++;
    *s = '\0';
}

int main(void)
{
    char s[100] = "ab\0c";
    char t[100] = "def";
    strcat_(s, t);
    puts(s);
    return EXIT_SUCCESS;
}
