/*  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2210.html

    Use Case - Atomic Types
    An effective and correct definition of the atomic types in
    N2145 C++ Atomic Types and Operations is a motivating use case for the
    proposal.

    The following code, as defined in this proposal and in conjunction
    with N2172, appears to satisfy the requirements of N2145, setting aside
    the issue of static initialization and inheritance.
*/

typedef struct atomic_int {
#ifdef __cplusplus
    // ~atomic_int() - destructor implicitly declared and defined
    atomic_int() = default;       // otherwise suppresed by other constructors
    atomic_int( int );            // construct from value
    int operator=(int) volatile;  // assign from value
    atomic_int(const atomic_int&) = delete;           // too dangerous
    atomic_int& operator=(const atomic_int&) = delete;// also
    operator int();          // load the value
private:
#endif
    int m_v;
} atomic_int;


atomic_int::atomic_int(int v) : m_v(v) { }
int atomic_int::operator=(int v) volatile {
    m_v = v;
    return v;
}
atomic_int::operator int() { return m_v; }

/*
  The destructor is implicitly defaulted and trivial.
  The default constructor is explicitly defaulted and trivial.
  The copy constructor and copy assignment operators are deleted and therefore
  trivial. As a result, the class is trivial and a POD, and may therefore
  be used in static, aggregate initialization.

  The erroneous defaults for copying are deleted, preventing their use.
  One can still copy from one atomic to another, but only going through a
  non-atomic value, which makes clear that a copy between two atomics is not
  itself atomic.
*/


atomic_int w = { 3 }; // static initialization with trivial members
atomic_int x; // default zero initialization
void function( atomic_int * p ) {
    // atomic_int y( *p ); ERROR - copy constructor is deleted
    atomic_int z( int(*p) ); // okay copy construct through value
    // *p = x;  ERROR - copy assignment is deleted
    *p = int(x); // okay copy assignment through value
}

main()
{
    function(&w);
}
