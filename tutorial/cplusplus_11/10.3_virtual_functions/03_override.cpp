/*  https://www.codeproject.com/Articles/570638/Ten-Cplusplus-Features-Every-Cplusplus-Developer#overrideandfinal

    Fortunately there is now a way to describe your intentions.
    Two new special identifiers (not keywords) have been added:
    > override , to indicate that a method is supposed to be an override
    of a virtual method in a base class, and
    > final , to indicate that a derived class shall not override a virtual
    method.
*/

#include <stdio.h>


// override example
class B {
public:
    virtual void f(short) { printf("B::f\n"); }
};


class D : public B {
public:
#if 0
    // 'virtual void D::f(int)' marked override, but does not override
    virtual void f(int) override  { printf("D::f\n"); }
#endif
};


main()
{
    B *d = new D;
    d->f(0);
}
