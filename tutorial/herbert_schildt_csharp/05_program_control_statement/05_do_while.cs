using System;

class Example
{
    static void Main()
    {
        // Display the digits of an integer in reverse order.
        int num;
        int nextdigit;

        num = 198;

        Console.WriteLine("Number: " + num);
        Console.Write("Number in reverse order: ");

        do
        {
            nextdigit = num % 10;
            Console.Write(nextdigit);
            num = num / 10;
        } while(num > 0);

        Console.WriteLine();
    }
}