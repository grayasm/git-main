/*
    Using an Action
    The Action delegate is used by Array.ForEach( ) to perform an action
    on each element of an array. There are various forms of Action, each
    taking a different number of type parameters.
    The one used here is:

public delegate void Action<in T> (T obj)

    The object to be acted upon is passed in obj. When used with ForEach( ),
    each element of the array is passed to obj in turn. Thus, through the
    use of ForEach( ) and Action, you can, in a single statement, perform
    an operation over an entire array.
*/


// Demonstrate an Action.
using System;


class MyClass
{
    public int i;

    public MyClass(int x) { i = x; }
}


class ActionDemo
{
    // An Action method.
    // It displays the value it is passed.

    static void Show(MyClass o)
    {
        Console.Write(o.i + " ");
    }

    // Another Action method.
    // It negates the value it is passed.
    static void Neg(MyClass o)
    {
        o.i = -o.i;
    }

    static void Main()
    {
        MyClass[] nums = new MyClass[5];
        nums[0] = new MyClass(5);
        nums[1] = new MyClass(2);
        nums[2] = new MyClass(3);
        nums[3] = new MyClass(4);
        nums[4] = new MyClass(1);

        Console.Write("Contents of nums: ");

        // Use action to show the values.
        Array.ForEach(nums, ActionDemo.Show);
        Console.WriteLine();

        // Use action to negate the values.
        Array.ForEach(nums, ActionDemo.Neg);
        Console.Write("Contents of nums negated: ");

        // Use action to negate the values again.
        Array.ForEach(nums, ActionDemo.Show);
        Console.WriteLine();
    }
}
