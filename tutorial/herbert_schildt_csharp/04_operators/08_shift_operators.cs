using System;

class Example
{
    static void Main()
    {

        // Demonstrate the shift << and >> operators.
        int val = 1;

        for(int i = 0; i < 8; i++)
        {
            for(int t=128; t > 0; t = t/2)
            {
                if((val & t) != 0) Console.Write("1 ");
                if((val & t) == 0) Console.Write("0 ");
            }
            Console.WriteLine();
            val = val << 1; // left shift
        }

        Console.WriteLine();

        val = 128;
        for(int i = 0; i < 8; i++)
        {
            for(int t=128; t > 0; t = t/2)
            {
                if((val & t) != 0) Console.Write("1 ");
                if((val & t) == 0) Console.Write("0 ");
            }
            Console.WriteLine();
            val = val >> 1; // right shift
        }


        // Use the shift operators to multiply and divide by 2.
        int n;
        n = 10;

        Console.WriteLine("Value of n: " + n);

        // Multiply by 2.
        n = n << 1;
        Console.WriteLine("Value of n after n = n * 2: " + n);

        // Multiply by 4.
        n = n << 2;
        Console.WriteLine("Value of n after n = n * 4: " + n);

        // Divide by 2.
        n = n >> 1;
        Console.WriteLine("Value of n after n = n / 2: " + n);

        // Divide by 4.
        n = n >> 2;
        Console.WriteLine("Value of n after n = n / 4: " + n);
        Console.WriteLine();

        // Reset n.
        n = 10;
        Console.WriteLine("Value of n: " + n);

        // Multiply by 2, 30 times.
        n = n << 30; // data is lost
        Console.WriteLine("Value of n after left-shifting 30 places: " + n);

        // Bitwise Compound Assignments
        n = n ^ 127;
        n ^= 127;
    }
}