/*
    Virtual Methods and Overriding
    A virtual method is a method that is declared as virtual in a base class.
    The defining characteristic of a virtual method is that it can be redefined
    in one or more derived classes. Thus, each derived class can have its own
    version of a virtual method. Virtual methods are interesting because of what
    happens when one is called through a base class reference. In this situation
    C# determines which version of the method to call based upon the type of the
    object referred to by the reference—and this determination is made at
    runtime. Thus, when different objects are referred to, different versions
    of the virtual method are executed. In other words, it is the type of the
    object being referred to (not the type of the reference) that determines
    which version of the virtual method will be executed. Therefore, if a base
    class contains a virtual method and classes are derived from that base class
    then when different types of objects are referred to through a base class
    reference, different versions of the virtual method can be executed.
*/

// Demonstrate a virtual method.

using System;


class Base
{
    // Create virtual method in the base class.
    public virtual void Who()
    {
        Console.WriteLine("Who() in Base");
    }
}

class Derived1 : Base
{
    // Override Who() in a derived class.
    public override void Who()
    {
        Console.WriteLine("Who() in Derived1");
    }
}

class Derived2 : Base
{
    // Override Who() again in another derived class.
    public override void Who()
    {
        Console.WriteLine("Who() in Derived2");
    }
}


class OverrideDemo
{
    static void Main()
    {
        Base baseOb = new Base();
        Derived1 dOb1 = new Derived1();
        Derived2 dOb2 = new Derived2();

        Base baseRef; // a base class reference
        baseRef = baseOb;
        baseRef.Who();

        baseRef = dOb1;
        baseRef.Who();

        baseRef = dOb2;
        baseRef.Who();
    }
}
