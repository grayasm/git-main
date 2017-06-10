using System;

class Example
{
    static void Main()
    {
        int i = 0;

        // Use break to exit this loop.
        for(i=-10; i <= 10; i++)
        {
            if(i > 0) break; // terminate loop when i is positive
            Console.Write(i + " ");
        }
        Console.WriteLine("Done");

        // Using break to exit a do-while loop.

        i = -10;
        do
        {
            if(i > 0) break;
            Console.Write(i + " ");
            i++;
        } while(i <= 10);

        Console.WriteLine("Done");


        // Find the smallest factor of a value.
        int factor = 1;
        int num = 1000;

        for(i=2; i <= num/i; i++)
        {
            if((num%i) == 0)
            {
                factor = i;
                break; // stop loop when factor is found
            }
        }
        Console.WriteLine("Smallest factor is " + factor);


        // Using break with nested loops.
        for(i=0; i<3; i++)
        {
            Console.WriteLine("Outer loop count: " + i);
            Console.Write(" Inner loop count: ");

            int t = 0;
            while(t < 100)
            {
                if(t == 10) break; // terminate loop if t is 10
                Console.Write(t + " ");
                t++;
            }

            Console.WriteLine();
        }

        Console.WriteLine("Loops complete.");
    }
}