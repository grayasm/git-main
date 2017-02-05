/*
    Runtime Type Identification
    C# includes three keywords that support runtime type identification:
    is, as, and typeof.
*/

// Demonstrate is.

using System;

class A {}
class B : A {}

class UseIs
{
    static void Main()
    {
        A a = new A();
        B b = new B();

        if(a is A)
            Console.WriteLine("a is an A");

        if(b is A)
            Console.WriteLine("b is an A because it is derived from A");

        if(a is B)
            Console.WriteLine("This won’t display -- a not derived from B");

        if(b is B)
            Console.WriteLine("b is a B");

        if(a is object)
            Console.WriteLine("a is an object");
    }
}
