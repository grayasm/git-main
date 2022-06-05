/*  This is an in depth tutorial about move semantics and rvalue references:
    http://thbecker.net/articles/rvalue_references/section_01.html

    Rvalue references solve at least 2 problems:
    > Implementing move semantics
    > Perfect forwarding
*/

#include <stdio.h>


main()
{
    /* 1. What are lvalues and rvalues in C++?
       lvalues may appear on both sides of the assignment (=)
       rvalues may appear only on the right side of the assignment (=)
    */
    int a = 42;
    int b = 43;
    // a and b are both l-values
    a = b;
    b = a;
    a = a * b;    // all 3 ok.

    int c = a * b;// rvalue on the right side of assignment (=)
#if 0
    a * b = 42;   // error, rvalue on the left side of assignment (=)
#endif

    /* 2. Here is an alternate definition which, although it can still be argued
       with, will put you in a position to tackle rvalue references:
       > An lvalue is an expression that refers to a memory location and allows
       us to take the address of that memory location via the & operator.
       > An rvalue is an expression that is not an lvalue.
     */

    // lvalues:
    int i = 42;
    i = 43;                // ok, i is an lvalue
    int *p = &i;           // ok, i is an lvalue
    extern int& foo();
    foo() = 42;            // ok, foo() is an lvalue
    int *p1 = &foo();      // ok, foo() is an lvalue

    // rvalues:
    extern int bar();
    int j = 0;
    j = bar();             // ok, bar() is an rvalue
#if 0
    int *p2 = &bar();      // error, cannot take the address of an rvalue
    bar() = 43;            // error, lvalue required as left operand
#endif

    j = 42;                // ok, 42 is an rvalue
}



int gival0 = 100;
int& foo() { return gival0; }
int bar() { return gival0; }
