/* Cap.4 Functions and Program Structure, pag.79

   Exercise 4-6: Add commands for handling variables. (It's easy to provide
                 twenty-six variables with single-letter names). Add a variable
                 for the most recently printed value.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NONE     0
#define LEFT     1
#define RIGHT    2
#define FUNCTION 3


int main()
{
    int c;
    double l, r;
    int state;
    int i;
    char ci[200];

    c = 0;
    l = r = 0.0;
    ci[0] = '\0';
    i = 0;
    state = NONE;


    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            state = NONE;
            i = 0;
            ci[0] = '\0';
            printf(" r=%f\n", l);
            l = r = 0.0;
            goto Next;
        }

        if ((state == NONE || state == LEFT) && c >= '0' && c <= '9') {
            ci[i++] = c;
            goto Next;
        }

        if (c == ' ' && state == NONE && i > 0) {
            ci[i] = '\0';
            l = atof(ci);
            state = LEFT;
            i = 0;
            goto Next;
        }

        if (c == ' ' && state == LEFT && i > 0) {
            ci[i] = '\0';
            r = atof(ci);
            state = RIGHT;
            i = 0;
            goto Next;
        }

        if (c == '-' || c == '+' || c == '/' || c == '*') {

            if (state == LEFT && i > 0) {          /* 4 3-  */
                ci[i] = '\0';
                r = atoi(ci);
            }
            else if (state == LEFT && i == 0)      /* 4 3 - + */
                goto Error;

            if (c == '-') l = l - r;
            else if (c == '+') l = l + r;
            else if (c == '/') l = l / r;
            else if (c == '*') l = l * r;

            r = 0;
            i = 0;
            state = LEFT;
            goto Next;
        }

        /* 180 90 - sin [with arg in degrees] */
        if (state == LEFT && c >= 'a' && c <= 'z') {
            ci[i++] = c;
            state = FUNCTION;
            goto Next;
        }

        if (state == FUNCTION && c >= 'a' && c <= 'z') {
            ci[i++] = c;
            goto Next;
        }

        if (c == ' ' && state == FUNCTION) {
            ci[i] = '\0';

            if      (strcmp(ci, "sin") == 0) l = sin(l * M_PI / 180.0);
            else if (strcmp(ci, "cos") == 0) l = cos(l * M_PI / 180.0);
            else if (strcmp(ci, "tan") == 0)
                l = sin(l * M_PI/180.) / cos(l * M_PI/180.0);

            r = 0;
            i = 0;
            ci[0] = '\0';
            state = LEFT;
            goto Next;
        }

        if (c == ' ' || c == '\t')
            goto Next;

    Error:
        printf("%c\nIllegal expression\n", c);
        break;


    Next:
        putchar(c);
    } /* while */


    return EXIT_SUCCESS;
}
