#include "func2.h"

namespace lib1
{
	int func1(int l, int r) // addition
	{
		return lib2::func2(l, r) + 10;
	}
}
