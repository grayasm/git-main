/* N3337, pag 110, 5.3.6 Alignof

   An alignof expression yields the alignment requirement of its operand type.
   The operand should be a (1) type-id representing a complete object type or
   (2) an array thereof or (3) a reference to a complete type.
   The result is an integral constant of type std::size_t.
   When alignof is applied to (3) a reference type, the result shall be the
   alignment of the reference type. When alignof is applied to (2) an array type
   the result shall be the alignment of the element type.
 */

#include <iostream>
using namespace std;


struct Foo
{
	int     i;
	float   f;
	char    c;
};

struct Empty {};

struct alignas(64) Empty64 {};

int main()
{
	cout << "Alignment of \n"
	     << "- char             : " << alignof(char) << std::endl
	     << "- pointer          : " << alignof(int*) << std::endl
	     << "- class Foo        : " << alignof(Foo)  <<  std::endl
	     << "- empty class      : " << alignof(Empty) << std::endl
	     << "- alignas(64) Empty: " << alignof(Empty64) << std::endl;

	return 0;
}
