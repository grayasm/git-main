/* Cap.4 Functions and Program Structure, pag.71

   Exercise 4-1: Write the function strrindex(s,t) which returns the position
                 of the rightmost occurrence of t in s, or -1 if there is none.
*/

#include <stdio.h>

int strrindex(char s[], char t[]);

main()
{
    char s[] = "long string - short string";
    char t[] = "string";

    printf("righmost position of %s in %s: %d\n", t, s, strrindex(s, t));
}

/* strrindex:  return index of rightmost t in s, -1 if none */
int strrindex(char s[], char t[])
{
    int i, j, k, rindex;

    rindex = -1;
    for (i = 0; s[i] != '\0'; i++) {
        /* check if t starts at this index in s */
        for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++);
        if (k > 0 && t[k] == '\0')  /* if it does ...*/
            rindex = i;             /* replace rindex with our find */
    }
    return rindex;
}
