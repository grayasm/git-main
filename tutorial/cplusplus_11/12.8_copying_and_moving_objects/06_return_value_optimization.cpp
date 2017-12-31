/*  This is an in depth tutorial about move semantics and rvalue references:
    http://thbecker.net/articles/rvalue_references/section_06.html

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


/*
  Any modern compiler will apply return value optimization to the original
  function definition. In other words, rather than constructing an X locally
  and then copying it out, the compiler would construct the X object directly
  at the location of foo's return value. Rather obviously, that's even better
  than move semantics.

  In order to really use rvalue references and move semantics in an optimal way,
  you need to fully understand and take into account today's compilers'
  "special effects" such as return value optimization and copy elision.
*/

X foo()
{
    X x(20);
    return x;
}

main()
{
    X y = foo();
}

/*
  X(int)
  ~X()
*/
