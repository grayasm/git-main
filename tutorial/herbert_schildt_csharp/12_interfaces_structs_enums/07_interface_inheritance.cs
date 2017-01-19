/*
    Interfaces Can Be Inherited
    One interface can inherit another. The syntax is the same as for inheriting
    classes. When a class implements an interface that inherits another
    interface, it must provide implementations for all the members defined
    within the interface inheritance chain.
*/

// One interface can inherit another.

using System;


public interface IA
{
    void Meth1();
    void Meth2();
}

// IB now includes Meth1() and Meth2() -- it adds Meth3().
public interface IB : IA
{
    void Meth3();
}


// This class must implement all of IA and IB.
class MyClass : IB
{
    public void Meth1()
    {
        Console.WriteLine("Implement Meth1().");
    }

    public void Meth2()
    {
        Console.WriteLine("Implement Meth2().");
    }

    public void Meth3()
    {
        Console.WriteLine("Implement Meth3().");
    }
}


class IFExtend
{
    static void Main()
    {
        MyClass ob = new MyClass();

        ob.Meth1();
        ob.Meth2();
        ob.Meth3();
    }
}
