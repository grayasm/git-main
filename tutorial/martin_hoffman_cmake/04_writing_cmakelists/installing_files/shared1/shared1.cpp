#include "shared1.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>


void get_random_name(std::string& name)
{
	int i = rand() % 1000;
	char buff[200];
	snprintf(buff, 199, "random-%d", i);
	name = buff;
}
