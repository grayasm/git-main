/*  This is an in depth tutorial about move semantics and rvalue references:
    http://thbecker.net/articles/rvalue_references/section_04.html

    Example of move constructor and move assignment operator implementation.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;


class X {
    int* ptr;
    size_t len;

public:
    explicit X(size_t sz) : ptr(new int[sz]), len(sz)
    {
        printf("X(size_t) len=%d\n", len);
    }

    ~X()
    {
        if(ptr != nullptr)
            delete [] ptr;
        printf("~X() len=%d\n", len);
    }

    X(const X& tc) : ptr(new int[tc.len]), len(tc.len)
    {
        printf("X(const X&) len=%d\n", len);
    }

    X& operator=(const X& tc)
    {
        if(this != &tc)
        {
            if(ptr != nullptr)
                delete [] ptr;
            ptr = new int[tc.len];
            len = tc.len;
            copy(tc.ptr, tc.ptr+len, ptr);
        }
        printf("operator(const X&) len=%d\n", len);
        return *this;
    }

    // implementing the move constructor
    X(X&& tm)
    {
        ptr = tm.ptr;
        len = tm.len;
        tm.ptr = nullptr;
        tm.len = 0;
        printf("X(X&&) len=%d\n", len);
    }

    // implementing the move assignment operator
    X& operator =(X&& tm)
    {
        if(this != &tm)
        {
            if(ptr != nullptr)
                delete [] ptr;
            ptr = tm.ptr;
            len = tm.len;
            tm.ptr = nullptr;
            tm.len = 0;
        }
        printf("operator=(X&&) len=%d\n", len);
        return *this;
    }
};


main()
{
    // create a vector and add a few elements to it
    vector<X> v;
    v.push_back(X(2));
    v.push_back(X(7));
    // insert a new element into the second position of the vector
    v.insert(v.begin() + 1, X(5));
}
/*
X(size_t) len=2            <- v.push_back(X(2));
X(X&&) len=2
~X() len=0
X(size_t) len=7            <- v.push_back(X(7));
X(X&&) len=7
X(const X&) len=2
~X() len=2
~X() len=0
X(size_t) len=5            <- v.insert(.. X(5));
X(X&&) len=5
X(const X&) len=2
X(const X&) len=7
~X() len=2
~X() len=7
~X() len=0
~X() len=2
~X() len=5
~X() len=7
*/
