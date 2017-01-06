using System;

class Example
{
    static void Main()
    {
        // Initializing a Variable
        int count = 10; // give count an initial value of 10
        char ch = 'X'; // initialize ch with the letter X
        float f = 1.2F; // f is initialized with 1.2

        int a, b = 8, c = 19, d; // b and c have initializations

        // Dynamic Initialization

        // Length of sides.
        double s1 = 4.0;
        double s2 = 5.0;

        // Dynamically initialize hypot.
        double hypot = Math.Sqrt( (s1 * s1) + (s2 * s2) );
        Console.Write("Hypotenuse of triangle with sides " +
        s1 + " by " + s2 + " is ");
        Console.WriteLine("{0:#.###}.", hypot);
    }
}