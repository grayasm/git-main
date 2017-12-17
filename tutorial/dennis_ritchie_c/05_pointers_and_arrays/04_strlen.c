/* Cap.5 Pointers and Arrays

   Testing and simple strlen(s) function.
 */


#include <stdio.h>


/* strlen: return length of string s */
int strlen_(char *s)
{
    int n;

    for (n = 0; *s != '\0'; ++s)
        n++;
    return n;
}


main()
{
    char a[] = "hello, world";
    char *pa = a;

    printf("%d\n", strlen_("hello, world"));
    printf("%d\n", strlen_(pa));
    printf("%d\n", strlen_(a));
}
