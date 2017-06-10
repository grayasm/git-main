using System;

class Example
{
    static void Main()
    {
        // In an expression the smaller size operand is promoted to
        // the type with bigger size.

        // A promotion surprise!
        byte b;
        b = 10;
        b = (byte) (b * b); // cast needed!!
        Console.WriteLine("b: "+ b);

        // Without the cast, the result of adding ch1 to ch2 would be int,
        // which can’t be assigned to a char.
        char ch1 = 'a', ch2 = 'b';
        ch1 = (char) (ch1 + ch2);

        // Using casts in an expression.
        double n;
        for(n = 1.0; n <= 10; n++)
        {
            Console.WriteLine("The square root of {0} is {1}",
                              n, Math.Sqrt(n));
            Console.WriteLine("Fractional part: {0}",
                              Math.Sqrt(n) - (int) Math.Sqrt(n) );
            Console.WriteLine();
        }
    }
}