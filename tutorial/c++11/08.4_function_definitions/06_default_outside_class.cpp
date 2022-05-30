/*  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2210.html

    Default Function Definition
    The definition form =default; indicates that the function's default
    definition should be used.

    As expected, this works when the definition is inside the class body,
    but it also works when the definition is outside the class body,
    but as with the current language, you must declare the function within
    the class body.
*/

struct type {
    type() = default;    // commonly specified redundancy is now efficient
    type(const type&);   // a simple declaration
    virtual ~type();     // virtual requires a declaration
};

inline type::type(const type&) = default;  // now efficient
type::~type() = default;                   // non-inline default definition


main()
{
    type ta;
    type tb = ta;
    type tc(ta);
}
