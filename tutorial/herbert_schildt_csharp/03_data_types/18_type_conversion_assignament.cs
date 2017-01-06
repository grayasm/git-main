using System;

class Example
{
    static void Main()
    {
        // Type Conversion and Casting
        int i;
        float f;
        i = 10;
        f = i; // assign an int to a float

        // Automatic Conversions
        long L;
        double D;
        L = 100123285L;
        D = L;
        Console.WriteLine("L and D: " + L + " " + D);

        // *** This program will not compile. ***
        D = 100123285.0;
        //L = D; // Illegal!!!
        Console.WriteLine("L and D: " + L + " " + D);
    }
}