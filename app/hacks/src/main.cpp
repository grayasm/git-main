
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include "unistd.hpp"
#include <limits.h>
#include "string.hpp"
#include "strconv.hpp"
#include "time.hpp"



int main(int, char**)
{
	using namespace misc;
	setvbuf(stdout, NULL, _IONBF, 0);
	
	misc::time t1;
	misc::time t2(2015, time::FEB, 29, 0, 0, 0);
	
	printf("\nt1 %s", t1.tostring().c_str());
	printf("\nt2 %s", t2.tostring().c_str());
	
	t2 += time::hourSEC;
	printf("\nt3 %s", t2.tostring().c_str());
	
	return 0;
}