// Using custom formats.
using System;


class PictureFormatDemo
{
    static void Main()
    {
        double num = 64354.2345;
        Console.WriteLine("Default format: " + num);

        // Display with 2 decimal places.
        Console.WriteLine("Value with two decimal places: " + "{0:#.##}", num);

        // Display with commas and 2 decimal places.
        Console.WriteLine("Add commas: {0:#,###.##}", num);

        // Display using scientific notation.
        Console.WriteLine("Use scientific notation: " + "{0:#.###e+00}", num);

        // Scale the value by 1000.
        Console.WriteLine("Value in 1,000s: " + "{0:#0,}", num);

        /* Display positive, negative, and zero
           values differently.
        */
        Console.WriteLine("Display positive, negative, " +
                          "and zero values differently.");

        Console.WriteLine("{0:#.#;(#.##);0.00}", num);
        num = -num;
        Console.WriteLine("{0:#.##;(#.##);0.00}", num);
        num = 0.0;
        Console.WriteLine("{0:#.##;(#.##);0.00}", num);

        // Display a percentage.
        num = 0.17;
        Console.WriteLine("Display a percentage: {0:#%}", num);
    }
}
