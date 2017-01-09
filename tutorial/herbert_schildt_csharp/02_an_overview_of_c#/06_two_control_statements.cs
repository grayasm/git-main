// Demonstrate the if.

using System;

class IfDemo
{
    static void Main()
    {
        int a, b, c;
        a = 2;
        b = 3;

        if(a < b) Console.WriteLine("a is less than b");

        // This won’t display anything.
        if(a == b) Console.WriteLine("you won’t see this");

        Console.WriteLine();

        c = a - b; // c contains -1

        Console.WriteLine("c contains -1");

        if(c >= 0) Console.WriteLine("c is non-negative");
        if(c < 0) Console.WriteLine("c is negative");

        Console.WriteLine();

        c = b - a; // c now contains 1

        Console.WriteLine("c contains 1");

        if(c >= 0) Console.WriteLine("c is non-negative");

        if(c < 0) Console.WriteLine("c is negative");
    }
}