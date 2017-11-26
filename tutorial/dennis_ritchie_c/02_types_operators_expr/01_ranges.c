/* Cap.2 Types, Operators and Expressions pag.36

   Exercise 2-1. Write a program to determine the ranges of char, short, int
                 and long variables, both signed and unsigned by printing the
                 appropriate values from standard headers.
*/

#include <stdio.h>
#include <limits.h>

main()
{
    printf("char min:%d max:%d unsigned:%u\n", CHAR_MIN, CHAR_MAX, UCHAR_MAX);
    printf("short min:%d max:%d unsigned:%u\n", SHRT_MIN, SHRT_MAX, USHRT_MAX);
    printf("int min:%d max:%d unsigned:%u\n", INT_MIN, INT_MAX, UINT_MAX);
    printf("long min:%ld max:%ld unsigned:%lu\n", LONG_MIN, LONG_MAX, ULONG_MAX);
}
