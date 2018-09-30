/* Cap.2 Types, Operators and Expressions, pag.48

   Exercise 2-5: Write the function any(s1, s2) which returns the first location
                 in the string s1 where any character from the string s2 occurs,
                 or -1 if s1 contains no characters from s2.
                 (The standard library function strpbrk does the same job but
                 returns a pointer to the location).
*/

#include <stdio.h>

int any(const char s1[], const char s2[])
{
    int i, j;

    for (i = 0; s1[i] != '\0'; ++i)
        for (j = 0; s2[j] != '\0'; ++j)
            if (s1[i] == s2[j])
                return i;
    return -1;
}

main()
{
    char s1[] = "abcdef";
    char s2[] = "def";
    printf ("any(%s, %s)=%d\n", s1, s2, any(s1, s2));
}
