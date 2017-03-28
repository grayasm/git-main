/*
    It is not necessary to override a virtual method. If a derived class does
    not provide its own version of a virtual method, then the one in the base
    class is used.
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


class Derived2 : Base
{
    // This class does not override Who().
}


class NoOverrideDemo
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
        baseRef.Who(); // calls Base's Who()
    }
}
