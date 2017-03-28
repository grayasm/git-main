/*
    When Are Constructors Called?
    In the foregoing discussion of inheritance and class hierarchies, an
    important question may have occurred to you: When a derived class object is
    created, whose constructor is executed first? The one in the derived class
    or the one defined by the base class? For example, given a derived class
    called B and a base class called A, is A’s constructor called before B’s,
    or vice versa? The answer is that in a class hierarchy, constructors are
    called in order of derivation, from base class to derived class.
    Furthermore, this order is the same whether or not base is used.
    If base is not used, then the default (parameterless) constructor of each
    base class will be executed.
*/

// Demonstrate when constructors are called.

using System;


// Create a base class.
class A
{
    public A()
    {
        Console.WriteLine("Constructing A.");
    }
}

// Create a class derived from A.
class B : A
{
    public B()
    {
        Console.WriteLine("Constructing B.");
    }
}

// Create a class derived from B.
class C : B
{
    public C()
    {
        Console.WriteLine("Constructing C.");
    }
}

class OrderOfConstruction
{
    static void Main()
    {
        C c = new C();
    }
}
