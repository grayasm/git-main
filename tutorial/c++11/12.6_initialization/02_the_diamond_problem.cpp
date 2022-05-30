/*  C++ ISO N3337.pdf pag.255

    Let's repeat this:
    You can delegate to another constructor only in the ctor initialization list

    ctor-initializer:
    : mem-initializer-list
            mem-initializer-list:
            mem-initializer ...opt
    mem-initializer:
            mem-initializer-id (expression-list opt)
            mem-initializer-id braced-init-list
    mem-initializer-id:
            class-or-decltype
            identifier

    If a mem-initializer-id is ambiguous because it designates both a direct
    non-virtual base class and an inherited virtual base class, the
    mem-initializer is ill-formed. (the dyamond problem)
*/

#include <stdio.h>

class A {
public:
    A() { };
};

class B : public virtual A {
public:
    B() =default;
};

class C : public A, public B {
public:
#if 0
    C() : A() { }  // ill-formed: which A?
#else
    C() =default;
#endif
};


main()
{
    C c;
}
