/*  https://www.codeproject.com/Articles/570638/Ten-Cplusplus-Features-Every-Cplusplus-Developer#overrideandfinal

    The usage of virtual keyword does not stop an error like overloading
    a virtual function in base class, instead of overriding it.
*/

#include <stdio.h>


class B {
public:
    virtual void f(short) { printf("B::f\n"); }
};

class D : public B {
public:
    virtual void f(int) { printf("D::f\n"); }
};

/* D::f is suppose to override B::f. However, the signature differ, one takes
   a short, one takes an int, therefore D::f is just another method with the
   same name, an overload and not an override.
*/


main()
{
    B *d = new D;
    d->f(0);
}
/*
B::f
*/
