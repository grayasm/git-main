/*
    The Value Type Contraint
    It is useful to restrict the generic type to a value type.
    Here is the general form of the value type constraint:

where T : struct

    In this case, the keyword struct specifies that T must be a value type.
    (Recall that structures are value types.) Thus, an attempt to use a
    reference type, such as string, for T will result in a compilation error.
*/

// Demonstrate a value type constraint.
using System;

struct MyStruct
{
    //...
}

class MyClass
{
    // ...
}


class Test<T> where T : struct
{
    T obj;
    public Test(T x)
    {
        obj = x;
    }
    // ...
}


class ValueConstraintDemo
{
    static void Main()
    {
        // Both of these declarations are legal.
        Test<MyStruct> x = new Test<MyStruct>(new MyStruct());
        Test<int> y = new Test<int>(10);

        // But, the following declaration is illegal!
        // Test<MyClass> z = new Test<MyClass>(new MyClass());
    }
}
