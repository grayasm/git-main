// Sort an array and search for a value.
using System;


class SortDemo
{
    static void Main()
    {
        int[] nums = { 5, 4, 6, 3, 14, 9, 8, 17, 1, 24, -1, 0 };

        // Display original order.
        Console.Write("Original order: ");

        foreach(int i in nums)
            Console.Write(i + " ");
        Console.WriteLine();

        // Sort the array.
        Array.Sort(nums);

        // Display sorted order.
        Console.Write("Sorted order: ");
        foreach(int i in nums)
            Console.Write(i + " ");
        Console.WriteLine();

        // Search for 14.
        int idx = Array.BinarySearch(nums, 14);
        Console.WriteLine("Index of 14 is " + idx);
    }
}
