using System;

class Example
{
    static void Main()
    {
        var e0 = 2.7183;
        var e1 = 2.7183F;

        // Demonstrate implicitly typed variables.
        // These are now implicitly typed variables. They
        // are of type double because their initializing
        // expressions are of type double.

        var s1 = 4.0;
        var s2 = 5.0;

        // Now, hypot is implicitly typed. Its type is double
        // because the return type of Sqrt() is double.

        var hypot = Math.Sqrt( (s1 * s1) + (s2 * s2) );
        Console.Write("Hypotenuse of triangle with sides " +
        s1 + " by " + s2 + " is ");
        Console.WriteLine("{0:#.###}.", hypot);
        // The following statement will not compile because
        // s1 is a double and cannot be assigned a decimal value.

        //s1 = 12.2M; // Error!

    }
}