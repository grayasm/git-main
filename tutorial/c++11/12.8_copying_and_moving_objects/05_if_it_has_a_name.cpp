/*  This is an in depth tutorial about move semantics and rvalue references:
    http://thbecker.net/articles/rvalue_references/section_05.html

    if-it-has-a-name rule:
    Things that are declared as rvalue reference can be lvalues or rvalues.
    The distinguishing criterion is: if it has a name, then it is an lvalue.
    Otherwise, it is an rvalue.


    void foo(X&& rval): rval is an lvalue

    Derived(Derived&& rhs)
    : Base(rhs)            // wrong: rhs is an lvalue
    : Base(std::move(rhs)) // good: calls Base(Base&& rhs)
*/

#include <stdio.h>

class X
{
public:
    explicit X(int) { printf("X(int)\n"); }

    X(const X& tc) { printf("X(const X&)\n"); }

    X& operator=(const X& tc) { printf("operator=(const X&)\n"); return *this; }

    ~X() { printf("~X()\n"); }

    X(X&& rvref) { printf("X(X&&)\n"); }

    X& operator=(X&& rvref) { printf("operator=(X&&)\n"); return *this; }
};

void foo(X&& x)
{
    printf("foo(X&&): begin\n");
    X anotherX = x;  /* calls X(const X&), because after the call, x is still
                        in scope and can be accessed
                     */
    printf("foo(X&&): end\n");
}

X&& bar()
{
    X x(10);
    printf("X&& bar(): end\n");
    return static_cast<X&&>(x);
}

main()
{
    foo(X(2));
    X y = bar(); /* calls X(X&&) because the thing on the right hand side
                    has no name
                 */
}

/*
  X(int)
  foo(X&&): begin
  X(const X&)              <- X anotherX = x;
  foo(X&&): end
  ~X()
  ~X()
  X(int)
  X&& bar(): end
  ~X()
  X(X&&)                   <- X y = bar();
  ~X()
*/
