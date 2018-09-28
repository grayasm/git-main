/* Cap.1 A Tutorial Introduction, pag.17

   Exerciese 1-6: Verify that the expression getchar() != EOF is 0 or 1.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Enter a char\n");
    printf("getchar() != EOF : %d\n", getchar() != EOF);
    return EXIT_SUCCESS;
}
