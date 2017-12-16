/* Cap.1 A Tutorial Introduction, pag.20

   Exercise 1-8: Write a program to count blanks, tabs and newlines.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c, nb, nt, nl;

    nb = nt = nl = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++nb;
        else if (c == '\t')
            ++nt;
        else if (c == '\n')
            ++nl;
    }
    printf("%d %d %d\n", nb, nt, nl);
    return EXIT_SUCCESS;
}
