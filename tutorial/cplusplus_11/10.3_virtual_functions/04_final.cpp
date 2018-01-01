/*  https://www.codeproject.com/Articles/570638/Ten-Cplusplus-Features-Every-Cplusplus-Developer#overrideandfinal

    Fortunately there is now a way to describe your intentions.
    Two new special identifiers (not keywords) have been added:
    > override , to indicate that a method is supposed to be an override
    of a virtual method in a base class, and
    > final , to indicate that a derived class shall not override a virtual
    method.
*/

#include <stdio.h>


/*  On the other hand if you intend to make a method impossible to override
    any more down the hierarchy, mark it as final. That can be in the base class
    or any derived class. If it's in a derived clas you can use both the
    override and final specifiers.
*/


class B {
public:
    virtual void f(int) { printf("B::f\n"); }
};

class D : public B {
public:
    virtual void f(int) override final { printf("D::f\n"); }
};

class F : public D {
public:
#if 0
    // error: overriding final function ‘virtual void D::f(int)’
    virtual void f(int) override { printf("F::f\n"); }
#endif
};


main()
{
    B *f = new F;
    f->f(0);
}
