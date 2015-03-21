
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include "string.hpp"


int main(int, char**)
{
	std::string s0;
	s0.assign(10, '\0');
	bool test = (s0 == "");
	bool res = test;

	return 0;
}