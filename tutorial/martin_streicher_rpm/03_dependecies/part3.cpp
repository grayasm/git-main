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

	cout << "Return flags indicating compile-time options." << endl;
	cout << "16 bits = " << (flags & (0 << 0) == 0 ? "y":"n") << endl;
	cout << "32 bits = " << (flags & (1 << 0) == 1 ? "y":"n") << endl;
	cout << "64 bits = " << (flags & (1 << 1) == 1 ? "y":"n") << endl;
	cout << "other   = " << (flags & 3 == 3 ?         "y":"n") << endl;

	cout << "Compiler, assembler, and debug options:" << endl;
	cout << "DEBUG   = " << (flags & (1 << 8)== 1 ? "y":"n") << endl;
	cout << "ASMV or ASMINF — use ASM code = " << (flags & (1 << 9) == 1 ? "y":"n") << endl;

	// etc.
	return 0;
}
