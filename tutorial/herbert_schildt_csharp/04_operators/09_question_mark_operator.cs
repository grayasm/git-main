using System;

class Example
{
    static void Main()
    {
        // Prevent a division by zero using the ?.
        int result;
        for(int i = -5; i < 6; i++)
        {
            result = i != 0 ? 100 / i : 0;
            if(i != 0)
                Console.WriteLine("100 / " + i + " is " + result);
        }


        // Divide by only even, non-zero values.

        for(int i = -5; i < 6; i++)
            if(i != 0 ? (i%2 == 0) : false)
                Console.WriteLine("100 / " + i + " is " + 100 / i);
    }
}