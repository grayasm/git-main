/*
    Runtime Type Identification
    C# includes three keywords that support runtime type identification:
    is, as, and typeof.
*/

// Demonstrate as.

using System;

class A {}
class B : A {}


class CheckCast
{
    static void Main()
    {
        A a = new A();
        B b = new B();

        b = a as B; // cast, if possible, if not assign null.

        if(b==null)
            Console.WriteLine("The cast in b = (B) a is NOT allowed.");
        else
            Console.WriteLine("The cast in b = (B) a is allowed");
    }
}
