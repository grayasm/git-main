/*
    Generic Class Hierarchies
    Generic classes can be part of a class hierarchy in just the same
    way as non-generic classes. Thus, a generic class can act as a base
    class or be a derived class. The key difference between generic and
    non-generic hierarchies is that in a generic hierarchy, any type
    arguments needed by a generic base class must be passed up the
    hierarchy by all derived classes. This is similar to the way that
    constructor arguments must be passed up a hierarchy.
*/

// A simple generic class hierarchy.
using System;

// A generic base class.
class Gen<T>
{
    T ob;
    public Gen(T o)
    {
        ob = o;
    }

    // Return ob.
    public T GetOb()
    {
        return ob;
    }
}


// A class derived from Gen.
class Gen2<T> : Gen<T>
{
    public Gen2(T o) : base(o)
    {
        // ...
    }
}


class GenHierDemo
{
    static void Main()
    {
        Gen2<string> g2 = new Gen2<string>("Hello");
        Console.WriteLine(g2.GetOb());
    }
}
