// Demonstrate various format specifiers.
using System;


class FormatDemo
{
    static void Main()
    {
        double v = 17688.65849;
        double v2 = 0.15;
        int x = 21;

        Console.WriteLine("{0:F2}", v); // fixed-point notation
        Console.WriteLine("{0:N5}", v); // fixed-point with comma separators
        Console.WriteLine("{0:e}", v);  // scientific notation
        Console.WriteLine("{0:r}", v);  // Parse() input numeric value
        Console.WriteLine("{0:p}", v2); // percentage
        Console.WriteLine("{0:X}", x);  // hexadecimal UPPERCASE
        Console.WriteLine("{0:D12}", x); // whole integer numeric data
        Console.WriteLine("{0:C}", 189.99); // currency
    }
}
