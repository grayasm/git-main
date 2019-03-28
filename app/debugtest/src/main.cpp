

#include <stdio.h>
#include "vector.hpp"



int main()
{
    stl::vector<int, stl::allocator<int>> ivec;
    ivec.push_back(10);
    ivec.push_back(20);
    int val = 0;
    val = ivec.front();
    val = ivec.back();
    for (stl::vector<int>::iterator it = ivec.begin();
        it != ivec.end(); ++it)
    {
        val = *it;
    }
    

	return 0;
}