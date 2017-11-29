/* Cap.4 Functions and Program Structure, pag. 71

   Functions returning non-integers.
   Dump into a file:
   1.10
   2.20
   3.30
   4.40
   and run the program with: 02_atof < file.txt
*/

#include <stdio.h>
#include <ctype.h>


/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)    /* skip white spaces */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}


#define MAXLINE 100

/* rudimentary calculator */
main()
{
    double sum, atof(char[]);
    char line[MAXLINE];
    int getline_(char line[], int max);

    sum = 0;
    while (getline_(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));
    return 0;
}



/* getline: get line into s, return length */
int getline_(char s[], int lim)
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
