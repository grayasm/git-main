#include <iostream>
#include <zlib.h>


using namespace std;
int main(int argc, char** argv)
{
	cout << "Depends on zlib" << endl;
#ifndef ZLIB_VERSION
	#error "need ZLIB_VERSION"
#endif
	cout << "ZLIB_VERSION=" << ZLIB_VERSION << endl;
	uLong flags = zlibCompileFlags();

	cout << "With compile-time options:" << endl;
	int bit16 = 0;
	int bit32 = 1;
	int bit64 = (1 << 1);
	int bitex = 3;
	cout << "16 bits = " << ((flags & bit16) == bit16 ? "y":"n") << endl;
	cout << "32 bits = " << ((flags & bit32) == bit32 ? "y":"n") << endl;
	cout << "64 bits = " << ((flags & bit64) == bit64 ? "y":"n") << endl;
	cout << "other   = " << ((flags & bitex) == bitex ? "y":"n") << endl;

	return 0;
}
