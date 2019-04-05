

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
//#include <vector>


int main()
{
    stl::vector<int> v1, v2;
    for (int i = 0; i < 5; ++i)
        v1.push_back(i);
    for (int i = 0; i < v1.size(); ++i)
        printf("%d ", v1[i]);

    stl::vector<int>::const_iterator ib = v1.begin(), ie = v1.end(); // [0->4]
    v2.insert(v2.end(), ib, ie);

    for (int i = 0; i < v2.size(); ++i)
        printf("%d ", v2[i]);

    return 0;
}