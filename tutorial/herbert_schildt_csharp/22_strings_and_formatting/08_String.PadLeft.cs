// Trimming and padding.
using System;


class TrimPadDemo
{
    static void Main()
    {
        string str = "test";
        Console.WriteLine("Original string: " + str);

        // Pad on left with spaces.
        str = str.PadLeft(10);
        Console.WriteLine("|" + str + "|");

        // Pad on right with spaces.
        str = str.PadRight(20);
        Console.WriteLine("|" + str + "|");

        // Trim spaces.
        str = str.Trim();
        Console.WriteLine("|" + str + "|");

        // Pad on left with #s.
        str = str.PadLeft(10, '#');
        Console.WriteLine("|" + str + "|");

        // Pad on right with #s.
        str = str.PadRight(20, '#');
        Console.WriteLine("|" + str + "|");

        // Trim #s.
        str = str.Trim('#');
        Console.WriteLine("|" + str + "|");
    }
}
