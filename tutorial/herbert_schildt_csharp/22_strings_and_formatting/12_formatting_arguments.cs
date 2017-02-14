using System;


class FormatDemo2
{
    static void Main()
    {
        // Format the same argument three different ways:
        Console.WriteLine("{0:F2} {0:F3} {0:e}", 10.12345);

        // Display arguments in non-sequential order.
        Console.WriteLine("{2:d} {0:d} {1:d}", 1, 2, 3);
    }
}
