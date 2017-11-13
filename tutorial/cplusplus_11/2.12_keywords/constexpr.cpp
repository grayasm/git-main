/*	Header   : core functionality
	Signature: N3337 7.1 Specifiers [dcl.spec]
			   decl-specifiers:
			   		storage-class-specifier
			   		type-specifier
			   		function-specifier
			   		friend
			   		typedef
			   		constexpr

	Description: defines an expression that can be evaluated at compile time.

	See also: http://en.cppreference.com/w/cpp/language/constant_expression
*/



#include <iostream>

constexpr int square(int x);        // OK: declaration
constexpr int buffsz = 1024;        // OK: definition

/*constexpr*/ struct pixel          // error: pixel is a type
{
	int x;
	int y;
	constexpr pixel(int);           // OK: declaration
};

constexpr pixel::pixel(int a)
  : x(square(a)), y(square(a))      // OK: definition
{
}

/*constexpr*/ pixel small(2);       // error: square not defined, so small(2)
// not constant (5.19), so constexpr not satisfied

constexpr int square(int x)         // OK: definition
{
	return x * x;
}

constexpr pixel large(4);           // OK: square defined

int next(/*constexpr*/ int x)       // error: not for parameters
{
	return x + 1;
}

extern /*constexpr*/ int memsz;     // error: not a definition


int main()
{
	return 0;
}
