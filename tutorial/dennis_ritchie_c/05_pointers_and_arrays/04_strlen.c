/* Cap.5 Pointers and Arrays

 */


#include <stdio.h>


/* strlen: return length of string s */
int strlen(char *s)
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

    printf("%d\n", strlen("hello, world"));
    printf("%d\n", strlen(pa));
    printf("%d\n", strlen(a));
}
