// Demonstrate optional arguments.

using System;


class OptionArgDemo
{
    static void OptArgMeth(int alpha, int beta=10, int gamma = 20)
    {
        Console.WriteLine("Here is alpha, beta, and gamma: " +
                          alpha + " " + beta + " " + gamma);
    }

    static void OptArgMeth(int alpha, double beta=10.0, double gamma = 20.0)
    {
        Console.WriteLine("Here is alpha, beta, and gamma: " +
                          alpha + " " + beta + " " + gamma);
    }

    static void Main()
    {
        // OptArgMeth(1); // Error! Ambiguous
    }
}
