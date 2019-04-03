

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>



int main()
{
    stl::allocator<int> a;
    int* p = a.allocate(2);
    for (int i = 0; i < 2; ++i)
        p[i] = i;

    p = a.allocate(10, p);
    if (p)
    for (int i = 2; i < 10; i++)
        p[i] = i * 10;

    for (int i = 0; i < 10; i++)
        printf("%d ", p[i]);
    
    return 0;
}