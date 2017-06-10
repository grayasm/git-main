// Demonstrate IComparable<T> and IEquatable<T>.
using System;


// Now MyClass implements IComparable<T> and IEquatable<T>.
class MyClass : IComparable<MyClass>, IEquatable<MyClass>
{
    public int Val;
    public MyClass(int x) { Val = x; }

    // Implement IComparable<T>.
    public int CompareTo(MyClass other)
    {
        return Val - other.Val; // Now, no cast is needed.
    }

    // Implement IEquatable<T>.
    public bool Equals(MyClass other)
    {
        return Val == other.Val;
    }

    // An override of Equals(Object).
    public override bool Equals(Object obj)
    {
        if(obj is MyClass)
            return Equals((MyClass) obj);
        return false;
    }
    // An override of GetHashCode().
    public override int GetHashCode()
    {
        return Val.GetHashCode();
    }
}


class CompareDemo
{
    // Require IEquatable<T> interface.
    public static bool IsIn<T>(T what, T[] obs) where T : IEquatable<T>
    {
        foreach(T v in obs)
            if(v.Equals(what)) // Uses Equals()
                return true;
        return false;
    }

    // Require IComparable<T> interface. This method assumes
    // a sorted array. It returns true if what is inside the range
    // of elements passed to obs.
    public static bool InRange<T>(T what, T[] obs) where T : IComparable<T>
    {
        if(what.CompareTo(obs[0]) < 0 ||
            what.CompareTo(obs[obs.Length-1]) > 0)
                return false;
        return true;
    }

    // Demonstrate comparisons.
    static void Main()
    {
        // Use IsIn() with int.
        int[] nums = { 1, 2, 3, 4, 5 };
        if(IsIn(2, nums))
            Console.WriteLine("2 is found.");

        if(IsIn(99, nums))
            Console.WriteLine("This won’t display.");

        // Use IsIn() with MyClass.
        MyClass[] mcs = { new MyClass(1),
                          new MyClass(2),
                          new MyClass(3),
                          new MyClass(4) };

        if(IsIn(new MyClass(3), mcs))
            Console.WriteLine("MyClass(3) is found.");

        if(IsIn(new MyClass(99), mcs))
            Console.WriteLine("This won’t display.");

        // Use InRange() with int.
        if(InRange(2, nums))
            Console.WriteLine("2 is within the range of nums.");

        if(InRange(1, nums))
            Console.WriteLine("1 is within the range of nums.");

        if(InRange(5, nums))
            Console.WriteLine("5 is within the range of nums.");

        if(!InRange(0, nums))
            Console.WriteLine("0 is NOT within the range of nums.");

        if(!InRange(6, nums))
            Console.WriteLine("6 is NOT within the range of nums.");

        // Use InRange() with MyClass.
        if(InRange(new MyClass(2), mcs))
            Console.WriteLine("MyClass(2) is within the range of mcs.");

        if(InRange(new MyClass(1), mcs))
            Console.WriteLine("MyClass(1) is within the range of mcs.");

        if(InRange(new MyClass(4), mcs))
            Console.WriteLine("MyClass(4) is within the range of mcs.");

        if(!InRange(new MyClass(0), mcs))
            Console.WriteLine("MyClass(0) is NOT within the range of mcs.");

        if(!InRange(new MyClass(5), mcs))
            Console.WriteLine("MyClass(5) is NOT within the range of mcs.");
    }
}
