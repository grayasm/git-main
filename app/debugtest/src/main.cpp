

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>


int main()
{
    int it[5] = { -1, -2, -3, -4, -5 };
    stl::vector<int> vi(it, it + 5);
    stl::vector<int> v2;

    stl::vector<int>::const_iterator i1 = vi.begin(), i2 = vi.end();
    v2.insert(v2.end(), i1, i2);    

    return 0;
}