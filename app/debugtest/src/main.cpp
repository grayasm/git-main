

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>



int main()
{
    stl::vector<int> vi;
    for (int i = 9; i > 0; i--)
        vi.push_back(i);

    stl::vector<int> v2;
    stl::vector<int>::reverse_iterator rit1, rit2;
    rit1 = vi.rbegin();
    rit2 = vi.rbegin() + 5;

    v2.assign(rit1, rit2);

    size_t sz = v2.size();
    for (int i = 0; i < v2.size(); ++i)
        printf("%d ", v2[i]);

    printf("\n");

    return 0;
}