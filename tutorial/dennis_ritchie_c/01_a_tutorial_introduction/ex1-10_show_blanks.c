/* Cap.1 A Tutorial Introduction, pag.20

   Exercise 1-10: Write a program to copy its input to its output, replacing
                  each tab by \t, each backspace by \b, each backslash by \\.
                  This makes tabs and backspaces visible in an unambiguous way.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        if (c == '\b')
            printf("\\b");
        if (c == '\\')
            printf("\\\\");
        else
            printf("%c", c);
    }
    return EXIT_SUCCESS;
}
