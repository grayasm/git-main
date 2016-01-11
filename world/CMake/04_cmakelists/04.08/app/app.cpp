// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dll2.h"

int main(int argc, char* argv[])
{
	Dll2 d;
	int res = d.func2(10, 10);
	printf("Dll2.func2 (10, 10) = 10 + 10 + 10 + (10+10) = %d\n", res);

	return 0;
}

