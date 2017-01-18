/*
    Base Class References and Derived Objects
    As you know, C# is a strongly typed language. Aside from the standard
    conversions and automatic promotions that apply to its value types, type
    compatibility is strictly enforced. Therefore, a reference variable for one
    class type cannot normally refer to an object of another class type.
*/

// This program will not compile.

using System;


class X
{
    int a;
    public X(int i) { a = i; }
}

class Y
{
    int a;
    public Y(int i) { a = i; }
}


class IncompatibleRef
{
    static void Main()
    {
        X x = new X(10);
        X x2;
        Y y = new Y(5);
        x2 = x;        // OK, both of same type
        x2 = y;        // Error, not of same type
    }
}
