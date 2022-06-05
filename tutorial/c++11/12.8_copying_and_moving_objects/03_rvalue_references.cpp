/*  This is an in depth tutorial about move semantics and rvalue references:
    http://thbecker.net/articles/rvalue_references/section_03.html

    Rvalue References:
    X&  - lvalue reference to X
    X&& - rvalue reference to X
*/

#include <stdio.h>
typedef int X;

void foo(X& x);  // lvalue reference overload
void foo(X&& x); // rvalue reference overload

main()
{
    X x;
    X foobar();

    foo(x); // argument is lvalue: calls foo(X&)
    foo(foobar()); // argument is rvalue: calls foo(X&&)

    /* rvalue references allow a function to branch at compile time
       (via overload resolution) on the condition "Am I being called on an
       lvalue or rvalue?
    */

    extern void bar(X&);       /* cannot be called with rvalues */
    extern void bar(const X&); /* can be called with both lvalues and rvalues
                                  but is not possible to distinguish them.
                               */
    extern void bar(X&&); /* can be called with rvalues but not with lvalues */
}


void foo(X& ) { printf("foo(X&) - lvalue\n"); }
void foo(X&& ){ printf("foo(X&&)- rvalue\n"); }
X foobar() { return X(0); }

/*
foo(X&) - lvalue
foo(X&&)- rvalue
*/
