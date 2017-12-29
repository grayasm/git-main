/*  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2210.html

    A more subtle example involves indirectly controlling the allocation
    of a type. Deleting the definition of a class-specific operator new
    will prevent allocation in free store because new expressions
    involving type will be ill-formed.
*/

#include <new>

struct type {
    void* operator new(std::size_t) = delete;
};


main()
{
    type ta;
    type tb = ta;
    type tc(ta);
}
