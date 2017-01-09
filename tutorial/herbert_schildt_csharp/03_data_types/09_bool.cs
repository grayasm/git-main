// Demonstrate bool values.

using System;

class BoolDemo
{
    static void Main()
    {
        bool b;
        b = false;

        Console.WriteLine("b is " + b);
        b = true;
        Console.WriteLine("b is " + b);

        // A bool value can control the if statement.
        if(b) Console.WriteLine("This is executed.");
        b = false;
        if(b) Console.WriteLine("This is not executed.");

        // Outcome of a relational operator is a bool value.
        Console.WriteLine("10 > 9 is " + (10 > 9));
    }
}