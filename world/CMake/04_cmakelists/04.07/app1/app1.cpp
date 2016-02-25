#include "static1.hpp"
#include "shared1.hpp"

#ifndef __static1_hpp__
#error "static1.hpp" is missing
#endif

#ifndef __shared1_hpp__
#error "shared1.hpp" is missing
#endif

int main(int argc, char** argv)
{
	int r=0,g=0,b=0;
    srand(time(NULL));
	get_random_color (r,g,b);
	std::string name;
	get_random_name (name);
	printf("\n\nfrom static1 I get a random color:%d,%d,%d",r,g,b);
	printf("\nfrom shared1 I get a random name:%s",name.c_str());
	printf("\ndone!\n\n");
	return 0;
}
