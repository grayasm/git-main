// Demonstrate the for loop.

using System;

class ForDemo
{
    static void Main()
    {
        int count;

        for(count = 0; count < 5; count = count+1)
            Console.WriteLine("This is count: " + count);

        Console.WriteLine("Done!");
    }
}
