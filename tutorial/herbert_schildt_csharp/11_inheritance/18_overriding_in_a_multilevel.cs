/*
    In the case of a multilevel hierarchy, if a derived class does not override
    a virtual method, then, while moving up the hierarchy, the first override
    of the method that is encountered is the one executed.
*/

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

class Derived2 : Derived1
{
    // This class also does not override Who().
}

class Derived3 : Derived2
{
    // This class does not override Who().
}


class NoOverrideDemo2
{
    static void Main()
    {
        Derived3 dOb = new Derived3();
        Base baseRef;    // a base class reference
        baseRef = dOb;
        baseRef.Who();   // calls Derived1's Who()
    }
}
