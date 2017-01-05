// Use byte.

using System;

class Use_byte
{
    static void Main()
    {
        byte x;
        int sum;

        sum = 0;
        for(x = 1; x <= 100; x++)
              sum = sum + x;

        Console.WriteLine("Summation of 100 is " + sum);
    }
}