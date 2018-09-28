/* Cap.1 A Tutorial Introduction, pag.20

   Exercise 1-9. Write a program to copy its input to its output, replacing
                 each string of one or more blanks by a single blank.
*/

#include <stdio.h>
#include <stdbool.h> // C99 bool type

main()
{
    int c;
    bool blank = false;

    while((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t') {
            blank = true;
            continue;
        }
        if (blank)
            putchar (' ');
        putchar (c);
        blank = false;
    }
}
