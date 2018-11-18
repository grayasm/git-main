/* Cap.7 Input and Output, pag.168

   Exercise 7-9: Functions like isupper can be implemented to save space or to
                 save time. Explore both possibilities.

   http://www.learntosolveit.com/cprogramming/Ex_7.9.html
*/


#include <stdio.h>
#include <stdlib.h>

int myisupper(int);

int main(void) {
    int c;

    while ((c = getchar()) != 'x')
    {
        if (c == '\n')
            continue;

        if (myisupper(c) == 1)
            printf("true\n");
        else
            printf("false\n");
    }
    return EXIT_SUCCESS;
}

int myisupper(int c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    else
        return 0;
}
