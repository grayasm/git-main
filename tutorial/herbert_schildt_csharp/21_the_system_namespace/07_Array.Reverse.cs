// Reverse an array.
using System;


class ReverseDemo
{
    static void Main()
    {
        int[] nums = { 1, 2, 3, 4, 5 };

        // Display original order.
        Console.Write("Original order: ");
        foreach(int i in nums)
            Console.Write(i + " ");
        Console.WriteLine();

        // Reverse the entire array.
        Array.Reverse(nums);

        // Display reversed order.
        Console.Write("Reversed order: ");
        foreach(int i in nums)
            Console.Write(i + " ");
        Console.WriteLine();

        // Reverse a range.
        Array.Reverse(nums, 1, 3);

        // Display reversed order.
        Console.Write("Range reversed: ");
        foreach(int i in nums)
            Console.Write(i + " ");
        Console.WriteLine();
    }
}
