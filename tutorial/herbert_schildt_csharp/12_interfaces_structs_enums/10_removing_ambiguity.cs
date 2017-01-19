/*
    Here is an example in which two interfaces are implemented and both interfaces declare
a method called Meth( ). Explicit implementation is used to eliminate the ambiguity inherent
in this situation.
*/

// Use explicit implementation to remove ambiguity.

using System;

interface IMyIF_A
{
    int Meth(int x);
}


interface IMyIF_B
{
    int Meth(int x);
}


/* MyClass implements both interfaces.
*/
class MyClass : IMyIF_A, IMyIF_B
{
    // Explicitly implement the two Meth()s.
    int IMyIF_A.Meth(int x)
    {
        return x + x;
    }

    int IMyIF_B.Meth(int x)
    {
        return x * x;
    }

    // Call Meth() through an interface reference.
    public int MethA(int x)
    {
        IMyIF_A a_ob;
        a_ob = this;
        return a_ob.Meth(x); // calls IMyIF_A
    }

    public int MethB(int x)
    {
        IMyIF_B b_ob;
        b_ob = this;
        return b_ob.Meth(x); // calls IMyIF_B
    }
}


class FQIFNames
{
    static void Main()
    {
        MyClass ob = new MyClass();

        Console.Write("Calling IMyIF_A.Meth(): ");
        Console.WriteLine(ob.MethA(3));

        Console.Write("Calling IMyIF_B.Meth(): ");
        Console.WriteLine(ob.MethB(3));
    }
}
