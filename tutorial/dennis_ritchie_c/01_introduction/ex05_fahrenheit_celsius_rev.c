/* Cap.1 A Tutorial Introduction, pag.14

   Exercise 1-5: Modify the temperature conversion program to print the table
                 in reverse order, that is from 300 degrees to 0.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    printf("  F    C  \n");
    printf("----------\n");

    fahr = upper;
    while (fahr >= lower) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr - step;
    }
    return EXIT_SUCCESS;
}
