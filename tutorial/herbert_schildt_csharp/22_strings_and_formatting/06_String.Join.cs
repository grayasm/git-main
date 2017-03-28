// Split and join strings.
using System;


class SplitAndJoinDemo
{
    static void Main()
    {
        string str = "One if by land, two if by sea.";
        char[] seps = {' ', '.', ',' };

        // Split the string into parts.
        string[] parts = str.Split(seps);
        Console.WriteLine("Pieces from split: ");

        for(int i=0; i < parts.Length; i++)
            Console.WriteLine(parts[i]);

        // Now, join the parts.
        string whole = String.Join(" | ", parts);
        Console.WriteLine("Result of join: ");
        Console.WriteLine(whole);
    }
}
