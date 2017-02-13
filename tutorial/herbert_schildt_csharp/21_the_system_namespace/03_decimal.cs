// Manually create a decimal number.
using System;


class CreateDec
{
    static void Main()
    {
        decimal d = new decimal(12345, 0, 0, false, 2);
        Console.WriteLine(d);
    }
}
