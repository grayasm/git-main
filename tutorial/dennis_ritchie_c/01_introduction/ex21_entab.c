/* Cap.1 A Tutorial Introduction, pag.34

   Exercise 1-21: Write a program entab that replaces strings of blanks with the
                  minimum number of tabs and blanks to achieve the same spacing.
                  Use the same stops as for detab. When either a tab or a single
                  blank would suffice to reach a tab stop, which should be given
                  preference?
*/


#include <stdio.h>

#define MAXLINE 1000
#define TAB_WIDTH 8

int getchars(char s[], int maxline);
void entab(char s1[], char s2[], int tabwidth);

int main(void)
{
    char s1[MAXLINE];
    char s2[MAXLINE];

    printf("Input some characters, then press enter:\n");
    while (getchars(s1, MAXLINE) == 0)
        ;

    entab(s1, s2, TAB_WIDTH);
    printf("entab result:\n%s\n", s2);

    return 0;
}

int getchars(char s[], int lim)
{
    int c, i, l;

    for (i = 0, l = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim - 1)
          s[l++] = c;
    s[l] = '\0';

    return l;
}

/* entab: copy characters in s1 to s2 and replace blanks with tabs */
void entab(char s1[], char s2[], int w)
{
    int i, j, l, c, blanks;
    int blanksenough;

    i = 0;
    l = 0;
    while ((c = s1[i]) != '\0') {
        if (c == ' ') {
            blanksenough = 1;
            blanks = w - i % w;
            for (j = 1; j < blanks; ++j)
                if (s1[i + j] != ' ') {
                    blanksenough = 0;
                    break;
                }
            if (blanksenough) {
                s2[l++] = '\t';
                i += blanks - 1;
            } else {
                s2[l++] = c;
            }
        } else {
            s2[l++] = c;
        }
        ++i;
    }
    s2[l] = '\0';
}
