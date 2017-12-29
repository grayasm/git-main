/* https://msdn.microsoft.com/en-us/library/dn457344.aspx

   Benefits of explicitly defaulted functions
   4) if a copy constructor, copy-assignment operator,
   move constructor, move-assignment operator or
   destructor is explicitly declared, then the following are not automatically
   generated:
   > no move constructor
   > no move-assignment operator
*/

#include <stdio.h>

class C {
public:
    C() { }
    // this disables the move ctor/op
    C(const C&) { }


    // disabled if not specified
    C(C&&)=default;
    C& operator=(C&&)=default;
};


main()
{
    C a;
    C b = a;
    C c(a);
}
