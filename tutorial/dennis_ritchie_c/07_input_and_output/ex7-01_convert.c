/* Cap.7 Input and Output, pag.153

   Exercise 7-1: Write a program that converts upper case to lower or lower
                 case to upper, depending on the name it is invoked with
                 as found in argv[0].
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SLASH '/'

char *splitpath(const char *);

int main(int argc, char **argv)
{
    char *name, c;

    if (argc <= 0)
        exit(-1);

    name = splitpath(argv[0]);

    if (strcmp(name, "lower") == 0)
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    else if (strcmp(name, "upper") == 0)
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    else {
        printf("Unknown name. I'm confused.\n");
        exit(-1);
    }
    return EXIT_SUCCESS;
}

/* splitpath:  returns file-name of without path */
char *splitpath(const char *file)
{
    int n, i;
    for (i = n = 0 ; file[i] != '\0'; ++i)
        if (file[i] == SLASH)
            n = i + 1;
    return strdup(file + n);
}
