/* https://msdn.microsoft.com/en-us/library/dn457344.aspx

   Benefits of explicitly defaulted functions
   3) if a move constructor or move-assignment operator is explicitly declared,
   then the following are not automatically generated:
   > no copy constructor
   > no copy-assignment operator
*/

#include <stdio.h>

class C {
public:
    C() { }
    C(const C&& rval) { }  // move constructor

    // when not specified these are disabled
    C(const C&) =default;
    C& operator=(const C&) =default;
};

main()
{
    C a;
    C b = a;
    C c(a);
}
