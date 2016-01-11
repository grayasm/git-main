// dll2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dll2.h"
#include "dll1.h"
#include <stdio.h>

Dll2::Dll2()
{
	printf("call into: %s\n", __FUNCTION__);
}

Dll2::~Dll2()
{
	printf("call into: %s\n", __FUNCTION__);
}

int Dll2::func2(int l, int r)
{
	Dll1 d;
	return d.func1(l, r) + 10;
}