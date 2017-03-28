/*
    Three Built-in Attributes
    C# defines many built-in attributes, but three are especially
    important because they apply to a wide variety of situations:
    AttributeUsage, Conditional, and Obsolete.
*/

// Demonstrate the Obsolete attribute.

using System;


class Test
{
    [Obsolete("Use MyMeth2, instead.")]
    public static int MyMeth(int a, int b)
    {
        return a / b;
    }

    // Improved version of MyMeth.
    public static int MyMeth2(int a, int b)
    {
        return b == 0 ? 0 : a /b;
    }

    static void Main()
    {
        // Warning displayed for this.
        Console.WriteLine("4 / 3 is " + Test.MyMeth(4, 3));

        // No warning here.
        Console.WriteLine("4 / 3 is " + Test.MyMeth2(4, 3));
    }
}
