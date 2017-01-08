using System;

class Example
{
    static void Main()
    {
        // Determine if a value is positive or negative.
        int i, j;
        int a, b, c, d, k;

        i = j = a = b = c = d = k = 10;

        for(i=-5; i <= 5; i++)
        {
            Console.Write("Testing " + i + ": ");
            if(i < 0)
                Console.WriteLine("negative");
            else
                Console.WriteLine("positive");
        }

        // Nested ifs
        if(i == 10)
        {
            if(j < 20)
                a = b;
            if(k > 100)
                c = d;
            else
                a = c; // this else refers to if(k > 100)

            a *= 2; // warning CS0291: The variable 'a' is assigned...
        }
        else
            a = d; // this else refers to if(i == 10)

        // The if-else-if Ladder; Determine smallest single-digit factor.

        int num;
        for(num = 2; num < 12; num++)
        {
            if((num % 2) == 0)
                Console.WriteLine("Smallest factor of " + num);
            else if((num % 3) == 0)
                Console.WriteLine("Smallest factor of " + num);
            else if((num % 5) == 0)
                Console.WriteLine("Smallest factor of " + num);
            else if((num % 7) == 0)
                Console.WriteLine("Smallest factor of " + num);
            else
                Console.WriteLine(num + " is not divisible by 2, 3, 5, or 7.");
        }
    }
}