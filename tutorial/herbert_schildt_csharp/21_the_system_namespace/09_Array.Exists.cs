/*
    Using a Predicate
    A predicate is a delegate of type System.Predicate that returns either
    true or false, based upon some condition. It is declared as shown here:
public delegate bool Predicate<in T> (T obj)

    The object to be tested against the condition is passed in obj.
    If obj satisfies that condition, the predicate must return true.
    Otherwise, it must return false. Predicates are used by several
    methods in Array, including Exists( ), Find( ), FindIndex( ),
    and FindAll( ).
*/


// Demonstrate Predicate delegate.
using System;


class PredDemo
{
    // A predicate method.
    // It returns true if v is negative.

    static bool IsNeg(int v)
    {
        if(v < 0)
            return true;
        return false;
    }

    static void Main()
    {
        int[] nums = { 1, 4, -1, 5, -9 };

        Console.Write("Contents of nums: ");
        foreach(int i in nums)
            Console.Write(i + " ");
        Console.WriteLine();

        // First see if nums contains a negative value.
        if(Array.Exists(nums, PredDemo.IsNeg))
        {
            Console.WriteLine("nums contains a negative value.");

            // Now, find first negative value.
            int x = Array.Find(nums, PredDemo.IsNeg);
            Console.WriteLine("First negative value is : " + x);
        }
        else
            Console.WriteLine("nums contains no negative values.");
    }
}
