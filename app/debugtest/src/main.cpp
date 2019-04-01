

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
//#include <vector>



int main()
{
    stl::vector<int> vi(10, 10);
    stl::vector<int> v2;
    stl::vector<int>::iterator it1, it2;
    it1 = vi.begin() + 3;
    it2 = vi.begin() + 5;

    v2.assign(it1, it2);

    size_t sz = v2.size();

    return 0;
}