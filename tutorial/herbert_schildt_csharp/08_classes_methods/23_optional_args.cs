// Demonstrate optional arguments.

using System;


class OptionArgDemo
{
    static void OptArgMeth(int alpha, int beta=10, int gamma = 20)
    {
        Console.WriteLine("Here is alpha, beta, and gamma: " +
                          alpha + " " + beta + " " + gamma);
    }

    static void Main()
    {
        // Pass all arguments explicitly.
        OptArgMeth(1, 2, 3);

        // Let gamma default.
        OptArgMeth(1, 2);

        // Let both beta and gamma default.
        OptArgMeth(1);
    }
}
