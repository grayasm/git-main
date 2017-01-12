// Use named arguments.

using System;


class NamedArgsDemo
{
    // Determine if one value is evenly divisible by another.
    static bool IsFactor(int val, int divisor)
    {
        if((val % divisor) == 0) return true;
        return false;
    }

    static void Main()
    {
        // The following show various ways in which IsFactor() can be called.
        // Call by use of positional arguments.
        if(IsFactor(10, 2))
            Console.WriteLine("2 is factor of 10.");

        // Call by use of named arguments.
        if(IsFactor(val: 10, divisor: 2))
            Console.WriteLine("2 is factor of 10.");

        // Order doesn’t matter with a named argument.
        if(IsFactor(divisor: 2, val: 10))
            Console.WriteLine("2 is factor of 10.");

        // Use both a positional argument and a named argument.
        if(IsFactor(10, divisor: 2))
            Console.WriteLine("2 is factor of 10.");
    }
}
