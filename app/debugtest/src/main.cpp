

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"



int main()
{
    stl::vector<int> vi(10, 10);
    stl::vector<int>::iterator cit = vi.begin();
    stl::vector<int>::iterator eit = vi.end();
    
    long diff = eit - cit;


    return 0;
}