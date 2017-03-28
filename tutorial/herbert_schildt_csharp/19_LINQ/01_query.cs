/*
    A Simple Query
    At this point, it will be helpful to work through a simple LINQ example.
    The following program uses a query to obtain the positive values contained
    in an array of integers:
*/


// Create a simple LINQ query.
using System;
using System.Linq;


class SimpQuery
{
    static void Main()
    {
        int[] nums = { 1, -2, 3, 0, -4, 5 };

        // Create a query that obtains only positive numbers.
        var posNums = from n in nums
                      where n > 0
                      select n;

        Console.Write("The positive values in nums: ");

        // Execute the query and display the results.
        foreach(int i in posNums)
            Console.Write(i + " ");
        Console.WriteLine();
    }
}
