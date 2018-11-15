/* Cap.4 Functions and Program Structure, pag.91

   Exercise 4-14: Define a macro swap(t,x,y) that interchanges two arguments
                  of type t. (Block structure will help.)
*/


#include<stdio.h>

#define swap(t,x,y) { t _z;         \
                      _z = x;       \
                      x = y;        \
                      y = _z; }

int main(void)
{
    char x, y;
    x = 'a';
    y = 'b';
    printf("x=%c \t y=%c\n", x, y);
    swap(char, x, y);
    printf("x=%c \t y=%c\n", x, y);
}