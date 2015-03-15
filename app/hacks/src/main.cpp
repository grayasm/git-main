
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include "string.hpp"


int main(int, char**)
{
	// ("red dragon").compare(4, 6, "dragon")
	std::string ls0("red dragon");
	std::string rs0("dragon");
	int ress0 = ls0.compare(4, 6, rs0);
	misc::string lm0(ls0.c_str());
	misc::string rm0(rs0.c_str());
	int resm0 = lm0.compare(4, 6, rm0);
	
	// ("red dragon").compare(4, 7, "dragon")
	int ress2 = ls0.compare(4, 7, rs0);
	int resm2 = lm0.compare(4, 7, rm0);

	// ("red dragon").compare(4, 7 "dragons")
	std::string rs2("dragons");
	int ress3 = ls0.compare(4, 7, rs2);
	misc::string rm2(rs2.c_str());
	int resm3 = lm0.compare(4, 7, rm2);


	// ("red dragon").compare(4, 6, "big dragon", 4, 6)
	std::string rs3("big dragon");
	int ress4 = ls0.compare(4, 6, rs3, 4, 6);
	misc::string rm3(rs3.c_str());
	int resm4 = lm0.compare(4, 6, rm3, 4, 6);

	rs3 = "two big dragons in fire";
	rm3 = "two big dragons in fire";
	ress4 = ls0.compare(4, 7, rs3, 8, 7);
	resm4 = lm0.compare(4, 7, rm3, 8, 7);




	return 0;
}