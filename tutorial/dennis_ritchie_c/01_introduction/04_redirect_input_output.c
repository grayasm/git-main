/* Cap.1 A Tutorial Introduction, pag.16

   You can write a surprising amount of useful code without knowing anything
   more about input and output.

   obs: redirect stdin to a file when running this program.
        ./04_redirect_input_output < temp.txt
*/

#include <stdio.h>

/* copy input to output; 2nd version */
main()
{
    int c;

    while ((c = getchar()) != EOF)
        putchar (c);
}
