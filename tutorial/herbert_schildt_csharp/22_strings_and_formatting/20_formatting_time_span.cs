// Format a TimeSpan.
using System;


class TimeSpanDemo
{
    static void Main()
    {
        DateTime start = DateTime.Now;

        // Output the numbers 1 through 1000.
        for(int i = 1; i <= 1000; i++)
        {
            Console.Write(i + " ");
            if((i % 10) == 0)
                Console.WriteLine();
        }

        Console.WriteLine();
        DateTime end = DateTime.Now;
        TimeSpan span = end - start;
        Console.WriteLine("Run time: {0:c}", span);
        Console.WriteLine("Run time: {0:g}", span);
        Console.WriteLine("Run time: {0:G}", span);
        Console.WriteLine("Run time: 0.{0:fff} seconds", span);
    }
}
