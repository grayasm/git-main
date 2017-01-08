using System;

class Example
{
    static void Main()
    {
        // Compute the order of magnitude of an integer.
        int num;
        int mag;

        num = 435679;
        mag = 0;
        Console.WriteLine("Number: " + num);

        while(num > 0)
        {
            mag++;
            num = num / 10;
        };

        Console.WriteLine("Magnitude: " + mag);


        // Compute integer powers of 2.
        int e;
        int result;

        for(int i=0; i < 10; i++)
        {
            result = 1;
            e = i;

            while(e > 0)
            {
                result *= 2;
                e--;
            }
            Console.WriteLine("2 to the " + i + " power is " + result);
        }
    }
}