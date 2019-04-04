

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>

int main()
{
    int iv[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    stl::vector<int> vi;
    for (int i = 0; i < 10; ++i)
        vi.push_back(iv[i]);

    vi.assign(vi.begin(), vi.end());

    for (int i = 0; i < 10; ++i)
        printf("%d ", vi[i]);


    

    return 0;
}