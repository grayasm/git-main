/* Cap.1 A Tutorial Introduction, pag.31

   Exercise 1-18:  Write a program to remove trailing blanks and tabs from each
                   line of input, and to delete entirely blank lines.
*/


#include <stdio.h>

#define MAXLINE 1000
int getline__(char s[], int lim);


int main()
{
    char s[MAXLINE];
    int len;

    while ((len = getline__(s, MAXLINE)) > 0) {
        while (--len > 0 && (s[len] == ' ' || s[len] == '\t' || s[len] == '\n'))
            ;
        if (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
            continue;
        if (len < MAXLINE - 2)
            s[++len] = '\n';
        if (len < MAXLINE - 1)
            s[++len] = '\0';
        printf("%s", s);
    }
    return 0;
}


int getline__(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;        
}
