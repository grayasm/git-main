

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>

class A
{
public:
    A() {}
    A(const A& a) {}
    A(A&& a) {}
};


A f()
{
    return A();
}

int main()
{
    A a(f());
    return 0;
}