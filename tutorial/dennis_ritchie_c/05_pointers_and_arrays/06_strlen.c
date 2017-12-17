/* Cap.5 Pointers and Arrays, cap.103

   Pointer subtraction : if p and q point to elements of the same array
   and p < q, then q - p + 1 is the number of elements from p to q inclusive.
   This fact can be used to write another version of strlen.
*/


#include <stdio.h>

/* strlen: return length of string s */
int strlen_(char *s)
{
    char *p = s;

    while (*p != '\0')
        p++;
    return p - s;
}


main()
{
    char a[] = "hello, world";
    char *pa = a;

    printf("%d\n", strlen_("hello, world"));
    printf("%d\n", strlen_(pa));
    printf("%d\n", strlen_(a));
}
