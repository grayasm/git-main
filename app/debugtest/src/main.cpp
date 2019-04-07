

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>


int main()
{
    int t[5] = { -1, -2, -3, -4, -5 };
    std::vector<int> v;
    v.assign(t, t + 5);
    const int* b = &v.front();
    const int* e = &v.back();
    b = b++;

    v.assign(b, e);
    v.assign(5, *b);


    for (int i = 0; i < v.size(); ++i)
        printf("%d ", v[i]);
    return 0;
}