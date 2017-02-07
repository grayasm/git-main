/*
    Three Built-in Attributes
    C# defines many built-in attributes, but three are especially
    important because they apply to a wide variety of situations:
    AttributeUsage, Conditional, and Obsolete.
*/

// Demonstrate the Conditional attribute.

#define TRIAL

using System;
using System.Diagnostics;


class Test
{
    [Conditional("TRIAL")]
    void Trial()
    {
        Console.WriteLine("Trial version, not for distribution.");
    }

    [Conditional("RELEASE")]
    void Release()
    {
        Console.WriteLine("Final release version.");
    }

    static void Main()
    {
        Test t = new Test();
        t.Trial(); // called only if TRIAL is defined
        t.Release(); // called only if RELEASE is defined
    }
}
