/*  I started the topic on delegating constructors with this tutorial:
    http://www.learncpp.com/cpp-tutorial/8-6-overlapping-and-delegating-constructors/

    Prior to C++11, calling a constructor explicitly from another constructor
    creates a temporary object, initializes the temporary object using the
    constructor, and then discards it, leaving your original object unchanged.

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
*/


#include <stdio.h>

class Foo
{
    int mA, mB;
public:
    Foo()
    {
        // code to do A
        mA = -101;
    }

    Foo(int value) : Foo() // use the above constructor to do A
    {
        // code to do B
        mB = value;
    }

    void show() const { printf("mA=%d mB=%d\n", mA, mB); }
};


main()
{
    Foo a, b(-99);
    a.show();
    b.show();
}
/*
mA=-101 mB=32766
mA=-101 mB=-99
*/
