/* Cap.5 Pointers and Arrays, pag.105

   We will illustrate more aspects of pointers and arrays by studying versions
   of two useful functions adapted from the standard library.
   Although the strcpy version 3 may seem cryptic at first sight, the notational
   convenience is considerable, and the idiom should be mastered, because you
   will see it frequently in C programs.
*/


#include <stdio.h>

/* strcpy: copy t to s; array subscript version */
void strcpy_(char *s, char *t)
{
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}


/* strcpy: copy t to s; pointer version 1 */
void strcpy__(char *s, char *t)
{
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

/* strcpy: copy t to s; pointer version 2 */
void strcpy___(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
}

/* strcpy: copy t to s; pointer version 3 */
void _strcpy(char *s, char *t)
{
    while(*s++ = *t++)
        ;
}


main()
{
    char a[15], b[] = "hello, world";
    _strcpy(a, b);
    printf("a=%s\n", a);
}
