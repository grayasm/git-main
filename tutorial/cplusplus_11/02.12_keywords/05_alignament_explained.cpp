/* Before jumping into alignas, alignof let's clarify the alignment first.
   See: http://en.cppreference.com/w/cpp/language/object#Alignment

   Alignment
   ----------
   Every object type has the property called alignment requirement, which is an
   integer value of type std::size_t, always power of 2, representing the number
   of bytes between successive addresses at which objects of this type can be
   allocated. The alignment requirement of a type can be queried with alignof
   or std::alignment_of. The pointer alignment function std::align can be used
   to obtain a suitably-aligned pointer within some buffer, and
   std::aligned_storage can be used to obtain suitably-aligned storage.

   Each object type imposes its alignment requirement on every object of that
   type. Stricter alignment with larger alignment requirement can be requested
   using alignas.

   In order to satisfy alignment requirements of all non-static members of a
   class, padding may be inserted after some of its members.
 */


#include <iostream>

/* Objects of type S can be allocated at any address because both S.a and S.b
   can be allocated at any address.
*/
struct S
{
	char a;    // size: 1, alignment: 1
	char b;    // size: 1, alignment: 1
};  // size: 2, alignment: 1

/* Objects of type X must be allocated at 4-byte boundaries because X.n must
   be allocated at 4-byte boundaries because int's alignment requirement
   is 4
 */
struct X
{
	int  n;    // size: 4, alignment: 4
	char c;    // size: 1, alignment: 1
	// 3 bytes padding
};  // size: 8, alignment: 4



int main()
{
	using namespace std;
	cout << "sizeof(S) = " << sizeof(S)
	     << " alignof(S) = " << alignof(S) << '\n';

	cout << "sizeof(X) = " << sizeof(X)
	     << " alignof(X) = " << alignof(X) << '\n';

	return 0;
}
