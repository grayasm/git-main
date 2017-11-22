#include <iostream>
using namespace std;
template<typename T>
void print(T, const char* tname);

/* Size and alignment of basic types
   bool     sizeof=1     alignof=1
   char     sizeof=1     alignof=1
   int      sizeof=4     alignof=4
   float    sizeof=4     alignof=4
   long     sizeof=8     alignof=8
   double   sizeof=8     alignof=8

   void*    sizeof=8     alignof=8
   lambda   sizeof=1     alignof=1
   char[2]  sizeof=2     alignof=1
   short[8] sizeof=16    alignof=2

   void (*f[5])(float**)
            sizeof=8     alignof=8

*/

struct S0 { };  // sizeof=1    alignof=1
class  C0 { };  // sizeof=1    alignof=1

class  C1 {
public:
	char   c2bytes[2]; // +2
	float  f4bytes;    // +4
	long   l8bytes;    // +8  *
	int    i24bytes[6];// +24
	C1(){}             // +1
	~C1(){}            // +1
};
/* C1: sizeof(C1) should be sum of all items = 40 bytes
   C1: alignof(C1) should be the type with the biggest size = 8 bytes
 */

class  C2 {
public:
	C2() {}  // +1
	~C2() {} // +1
	C1 c1;   // +40
};

/* C2: sizeof(C2) sum of all items = 40; ?? don't understand why__
   C2: alignof(C2) biggest type = 8;     ?? again why__
 */


// class alignas(12) C12 { };   error: requested alignment is not a power of 2
class alignas(4)   C4 { };
class alignas(8)   C8 { };
class alignas(16)  C16 { };
class alignas(32)  C32 { };
class alignas(64)  C64 { };    // you get the idea: 2^6

class alignas(8) C8x
{
	C32 mc32;
};
// alignas(8) is not obeyed here, this class has alignment = 32


int main()
{
    print<bool>(true, "bool");
    print<char>('c', "char");
    print<int>(24, "int");
    print<float>(3.2f, "float");
    print<long>(300, "long");
    print<double>(3.3, "double");

    cout << endl;

    print<void*>(new int(33), "void*");

    auto ptolambda = [&](int,int,int) -> int { return 0; };
    print<>(ptolambda, "lambda");

    char c2[2] = "1";
    print<char[2]>(c2, "char[2]");

    short s8[8];
    print<short[8]>(s8, "short[8]");

    void (*f[5])(float***);
    print(f[5], "(*f[5])(..)");

    print<S0>(S0(), "S0");
    print<C0>(C0(), "C0");
    print<C1>(C1(), "C1");

    C2 class2;
    class2.c1;
    print<C2>(class2, "C2");

    C8x c8x;
    print<>(c8x, "C8x");

    return 0;
}


template<typename T>
void print(T, const char* tname)
{
    cout << "sizeof(" << tname << ")=" << sizeof(T) << " ";
    cout << "alignof(" << tname << ")=" << alignof(T) << endl;
}
