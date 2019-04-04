

#include <stdio.h>
#include <list>
#include <limits>
#include "vector.hpp"
#include <vector>



int main()
{
    stl::vector<float> fv;
    for (float f = 0.f; f < 10.f; f += 1.1f)
        fv.push_back(f);

    for (int i = 0; i < fv.size(); ++i)
        printf("%f ", fv[i]);
    
    return 0;
}