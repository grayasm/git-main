/*  This is an in depth tutorial about move semantics and rvalue references:
    http://thbecker.net/articles/rvalue_references/section_02.html

    This is a use case for the move contructor.
    X x;
    // do something with x
    extern X foo();
    x = foo();
*/

#include <stdio.h>


class X
{
public:
    explicit X(int)  // disable default (autogen) constructor
    {
        printf("X(int)\n");
    }

    X(const X& tc)
    {
        printf("X(const X&)\n");
    }

    X& operator=(const X& tc)
    {
        printf("operator=(const X&)\n"); return *this;
    }

    ~X() { printf("~X()\n"); }
};


X foo()
{
    static X x(1);  /* if not static, g++ 4.8.5 will skip the copy constructor
                       and will move the data from temporary x directly into y
                       which was not expected. I even forced -std=c++03 with
                       no luck. It should be obviously that the return X is
                       a temporary. Apparently this is called 'return value
                       optimization', and any modern compiler knows about it.
                       see sample 06_ .cpp
                     */
    return x;
}

main()
{
    X y = foo();  /* to avoid extra copying on this instruction we would need
                     move semantics.
                   */
}

/*
X(int)
X(const X&)
~X()
~X()
*/
