/* Cap.5 Pointers and Arrays, pag. 95

   Pointers and function arguments
*/

#include <stdio.h>


// void swap(int x, int y)    /* WRONG  , because of call by value */
void swap(int *px, int *py)
{
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
}


main()
{
    int a = 10, b = 20;

    swap(&a, &b);

    printf("a=%d b=%d\n", a, b);
}
