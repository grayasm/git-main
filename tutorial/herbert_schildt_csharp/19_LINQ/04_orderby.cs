/*
    Sort Results with orderby
    You can use orderby to sort on one or more criteria.

orderby sort-on how
*/


// Demonstrate orderby.
using System;
using System.Linq;


class OrderbyDemo
{
    static void Main()
    {
        int[] nums = { 10, -19, 4, 7, 2, -5, 0 };

        // Create a query that obtains the values in sorted order.
        var posNums = from n in nums
                      orderby n
                      select n;

        Console.Write("Values in ascending order: ");
        // Execute the query and display the results.
        foreach(int i in posNums)
            Console.Write(i + " ");
        Console.WriteLine();
    }
}
