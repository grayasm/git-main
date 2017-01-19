// Demonstrate the ISeries interface.

using System;


class SeriesDemo
{
    static void Main()
    {
        ByTwos ob = new ByTwos();

        Console.WriteLine("\nStarting at 100");
        ob.SetStart(100);

        for(int i=0; i < 5; i++)
            Console.WriteLine("Prev value is " + ob.GetPrevious());
    }
}
