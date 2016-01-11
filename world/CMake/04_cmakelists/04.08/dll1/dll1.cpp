// dll1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dll1.h"
#include "func1.h"
#include <stdio.h>

Dll1::Dll1()
{
	printf("call into: %s\n", __FUNCTION__);
}

Dll1::~Dll1()
{
	printf("call into: %s\n", __FUNCTION__);
}

int Dll1::func1(int l, int r)
{
	return lib1::func1(l, r) + 10;
}