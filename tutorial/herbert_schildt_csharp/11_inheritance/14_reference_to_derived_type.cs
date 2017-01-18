/*
    In general, an object reference variable can refer only to objects of its type.
There is, however, an important exception to C#’s strict type enforcement. A reference
variable of a base class can be assigned a reference to an object of any class derived from
that base class. This is legal because an instance of a derived type encapsulates an instance
of the base type. Thus, a base class reference can refer to it.
*/

// A base class reference can refer to a derived class object.

using System;

class X
{
    public int a;

    public X(int i)
    {
        a = i;
    }
}

class Y : X
{
    public int b;

    public Y(int i, int j) : base(j)
    {
        b = i;
    }
}


class BaseRef
{
    static void Main()
    {
        X x = new X(10);
        X x2;
        Y y = new Y(5, 6);
        x2 = x; // OK, both of same type

        Console.WriteLine("x2.a: " + x2.a);
        x2 = y; // OK because Y is derived from X

        Console.WriteLine("x2.a: " + x2.a);
        // X references know only about X members
        x2.a = 19; // OK
        // x2.b = 27; // Error, X doesn't have a b member
    }
}
