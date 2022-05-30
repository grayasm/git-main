/*  https://www.codeproject.com/Articles/570638/Ten-Cplusplus-Features-Every-Cplusplus-Developer#overrideandfinal

    Here is another subtle error. The parameters are the same, but the method
    in the base class is marked const, while the method in the derived is not.
 */

#include <stdio.h>


class B {
public:
    virtual void f(int) const { printf("B::f\n"); }
};

class D : public B {
public:
    virtual void f(int) { printf("D::f\n"); }
};



main()
{
    B *d = new D;
    d->f(0);
}
/*
B::f
*/
