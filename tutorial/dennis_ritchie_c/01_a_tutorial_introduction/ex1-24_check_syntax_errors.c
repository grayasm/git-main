/* Cap.1 A Tutorial Introduction, pag.34

   Exercise 1-24: Write a program to check a C program for rudimentary syntax
                  errors like unbalanced parantheses, brackets and braces.
                  Don't forget about quotes, both single and double, escape
                  sequences, and comments. (This program is hard if you do it
                  in full generality).
*/

#include <stdio.h>
#include <stdlib.h>


#define PROGRAM 0
#define COMMENT 1    /* inside /*...     */
#define STRING  2    /* double quote "a" */
#define QUOTE   3    /* single quote 'a' */

int main()
{
    int a, b, c;
    int parantheses, brackets, braces;
    int col, row;
    int state;

    state = PROGRAM;
    parantheses = brackets = braces = 0;
    col = row = 0;
    a = b = c = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            col = 0; row++;
            goto Next;
        }
        else if (c == '\t') {
            col += 4;
            goto Next;
        }
        else if (c == ' ') {
            col++;
            goto Next;
        }
        else
            col++;

        if (state == PROGRAM && b == '/' && c == '*') {
            state = COMMENT;
            goto Next;
        }

        if (state == COMMENT && a != '/' && b == '*' && c == '\\') {
            state = PROGRAM;
            goto Next;
        }

        if (state == PROGRAM && c == '"') {
            state = STRING;
            goto Next;
        }
        if (state == STRING && c == '"') {
            state = PROGRAM;
            goto Next;
        }

        if (state == PROGRAM && c == '\'') {
            state = QUOTE;
            goto Next;
        }
        if (state == QUOTE && c == '\'') {
            state = PROGRAM;
            goto Next;
        }


        if (state == PROGRAM && c == '(') {
            parantheses++;
            goto Next;
        }
        if (state == PROGRAM && c == ')') {
            if (--parantheses < 0) {
                putchar(c);
                printf("\n%d:%d cannot match ) symbol\n", row, col);
                break;
            }
        }

        if (state == PROGRAM && c == '[') {
            brackets++;
            goto Next;
        }
        if (state == PROGRAM && c == ']') {
            if (--brackets < 0) {
                putchar(c);
                printf("\n%d:%d cannot match ] symbol\n", row, col);
                break;
            }
        }

        if (state == PROGRAM && c == '{') {
            braces++;
            goto Next;
        }
        if (state == PROGRAM && c == '}') {
            if (--braces < 0) {
                putchar(c);
                printf("\n%d:%d cannot match } symbol\n", row, col);
                break;
            }
        }

    Next:
        a = b;
        b = c;
        putchar(c);
    } /* while */


    if (parantheses > 0)
        printf("\n%d:%d expected ) symbol %d time\n", row, col, abs(parantheses));
    if (brackets > 0)
        printf("\n%d:%d expected ] symbol %d times\n", row, col, abs(brackets));
    if (braces > 0)
        printf("\n%d:%d expected } symbol %d times\n", row, col, abs(braces));


    return EXIT_SUCCESS;
}
