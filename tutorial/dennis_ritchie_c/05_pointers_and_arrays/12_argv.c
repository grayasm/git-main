/* Cap.5 Pointers and Arrays, pag.115
 */

#include <stdio.h>


/* this version treats argv as an array of character pointers */
void print_argv(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc-1) ? " " : "");
    printf("\n");
}

void print_argv_(int argc, char *argv[])
{
    while(--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
    printf("\n");
}

main(int argc, char *argv[])
{
    print_argv(argc, argv);
    print_argv_(argc, argv);
}
