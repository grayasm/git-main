/*
    In object-oriented programming it is sometimes helpful to define what a
    class must do, but not how it will do it. In C#, you can fully separate
    a class’ interface from its implementation by using the keyword interface.

    Interfaces are syntactically similar to abstract classes. However, in an
    interface, no method can include a body. That is, an interface provides
    no implementation whatsoever. It specifies what must be done, but not how.
    Once an interface is defined, any number of classes can implement it.
    Also, one class can implement any number of interfaces.

    To implement an interface, a class must provide bodies (implementations)
    for the methods described by the interface. Each class is free to determine
    the details of its own implementation. Thus, two classes might implement
    the same interface in different ways, but each class still supports
    the same set of methods.

    Therefore, code that has knowledge of the interface can use objects of
    either class since the interface to those objects is the same. By providing
    the interface, C# allows you to fully utilize the "one interface,
    multiple methods" aspect of polymorphism.

     Here is a simplified form of an interface declaration:

interface name {
ret-type method-name1(param-list);
ret-type method-name2(param-list);
    // ...
ret-type method-nameN(param-list);
}

    To implement an interface, the name of the interface is specified after
    the class name in just the same way that a base class is specified.
    The general form of a class that implements an interface is shown here:

class class-name : interface-name {
 // class-body
}


    When a class implements an interface, the class must implement the entire
    interface. It cannot pick and choose which parts to implement, for example.
    A class can implement more than one interface. When a class implements more
    than one interface, specify each interface in a comma-separated list.
    A class can inherit a base class and also implement one or more interfaces.
    In this case, the name of the base class must come first in the
    comma-separated list.

    The methods that implement an interface must be declared public. The reason
    for this is that methods are implicitly public within an interface, so
    their implementation must also be public. Also, the return type and
    signature of the implementing method must match exactly the return type
    and signature specified in the interface definition.
*/

// Demonstrate the ISeries interface.
using System;


public interface ISeries
{
    int GetNext();    // return next number in series
    void Reset();     // restart
    void SetStart(int x);  // set starting value
}


// Implement ISeries.
class ByTwos : ISeries
{
    int start;
    int val;

    public ByTwos()
    {
        start = 0;
        val = 0;
    }

    public int GetNext()
    {
        val += 2;
        return val;
    }

    public void Reset()
    {
        val = start;
    }

    public void SetStart(int x)
    {
        start = x;
        val = start;
    }
}


class SeriesDemo
{
    static void Main()
    {
        ByTwos ob = new ByTwos();

        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob.GetNext());

        Console.WriteLine("\nResetting");
        ob.Reset();

        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob.GetNext());

        Console.WriteLine("\nStarting at 100");
        ob.SetStart(100);

        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob.GetNext());
    }
}
