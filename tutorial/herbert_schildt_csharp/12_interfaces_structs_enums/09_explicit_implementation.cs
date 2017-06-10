/*
    Explicit Implementations
    When implementing a member of an interface, it is possible to fully
    qualify its name with its interface name. Doing this creates an explicit
    interface member implementation, or explicit implementation, for short.
*/


// Explicitly implement an interface member.

using System;

interface IEven
{
    bool IsOdd(int x);
    bool IsEven(int x);
}


class MyClass : IEven
{
    /* Explicit implementation. Notice that this member is private
       by default.
    */
    bool IEven.IsOdd(int x)
    {
        if((x%2) != 0) return true;
        else return false;
    }

    // Normal implementation.
    public bool IsEven(int x)
    {
        IEven o = this; // Interface reference to the invoking object.
        return !o.IsOdd(x);
    }
}


class Demo
{
    static void Main()
    {
        MyClass ob = new MyClass();

        bool result;

        result = ob.IsEven(4);

        if(result) Console.WriteLine("4 is even.");

        result = ob.IsOdd(4); // Error, IsOdd not exposed.

        // But, this is OK. It creates an IEven reference to a MyClass object
        // and then calls IsOdd() through that reference.

        IEven iRef = (IEven) ob;
        result = iRef.IsOdd(3);
        if(result) Console.WriteLine("3 is odd.");
    }
}
