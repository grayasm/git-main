using System;

class StaticError
{
    public int Denom = 3; // a normal instance variable
    public static int Val = 1024; // a static variable

    /* Error! Can't directly access a non-static variable
       from within a static method. */

    static int ValDivDenom()
    {
        // return Val / Denom; // won't compile!

        return 1; // pass Makefile
    }
}


class AnotherStaticError
{
    // A non-static method.
    void NonStaticMeth()
    {
        Console.WriteLine("Inside NonStaticMeth().");
    }

    /* Error! Can't directly call a non-static method
       from within a static method. */
    static void staticMeth()
    {
        // NonStaticMeth(); // won't compile
    }
}


class MyClass
{
    // A non-static method.
    void NonStaticMeth()
    {
        Console.WriteLine("Inside NonStaticMeth().");
    }

    /* Can call a non-static method through an
       object reference from within a static method. */
    public static void staticMeth(MyClass ob)
    {
        ob.NonStaticMeth(); // this is OK
    }
}


class Ex
{
    static void Main()
    {
    }
}