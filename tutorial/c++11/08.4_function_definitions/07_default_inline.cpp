/*  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2210.html

    Trivial Definitions
    Critical to exploiting the benefits of N2172, an inline and explicitly
    defaulted definition is trivial if and only if the implicit definition
    would have been trivial. The potential concern with out-of-class definition
    is How is the compiler to know if it is trivial? The existing rule that an
    inline definition must occur before any use suffices here as well.
*/

#include <stdio.h>


struct type {
    type() = default; // trivial
    virtual ~type() = default; // non-trivial because virtual
    type& operator=(const type&); // declaration and ...
};

inline type& type::operator=(const type&) = default; // inline keeps it trivial


main()
{
    type ta;
    type tb = ta;
    type tc(ta);
}
