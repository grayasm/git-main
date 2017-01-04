// Demonstrate a block of code.

using System;

class BlockDemo
{
    static void Main()
    {
        int i, j, d;
        i = 5;
        j = 10;

        // The target of this if is a block.
        if(i != 0)
        {
            Console.WriteLine("i does not equal zero");

            d = j / i;

            Console.WriteLine("j / i is " + d);
        }
    }
}