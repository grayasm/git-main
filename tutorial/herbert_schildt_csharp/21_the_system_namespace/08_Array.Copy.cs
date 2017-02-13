// Copy an array.
using System;


class CopyDemo
{
    static void Main()
    {
        int[] source = { 1, 2, 3, 4, 5 };
        int[] target = { 11, 12, 13, 14, 15 };
        int[] source2 = { -1, -2, -3, -4, -5 };

        // Display source.
        Console.Write("source: ");
        foreach(int i in source)
            Console.Write(i + " ");
        Console.WriteLine();

        // Display original target.
        Console.Write("Original contents of target: ");
        foreach(int i in target)
            Console.Write(i + " ");
        Console.WriteLine();

        // Copy the entire array.
        Array.Copy(source, target, source.Length);

        // Display copy.
        Console.Write("target after copy: ");
        foreach(int i in target)
            Console.Write(i + " ");
        Console.WriteLine();

        // Copy into middle of target.
        Array.Copy(source2, 2, target, 3, 2);

        // Display copy.
        Console.Write("target after copy: ");
        foreach(int i in target)
            Console.Write(i + " ");
        Console.WriteLine();
    }
}
