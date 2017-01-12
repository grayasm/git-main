// Use static.

using System;


class StaticDemo
{
    // A static variable.
    public static int Val = 100;

    // A static method.
    public static int ValDiv2()
    {
        return Val/2;
    }
}


class SDemo
{
    static void Main()
    {
        Console.WriteLine("Initial value of StaticDemo.Val is "
                          + StaticDemo.Val);

        StaticDemo.Val = 8;
        Console.WriteLine("StaticDemo.Val is " + StaticDemo.Val);
        Console.WriteLine("StaticDemo.ValDiv2(): " +
        StaticDemo.ValDiv2());
    }
}
