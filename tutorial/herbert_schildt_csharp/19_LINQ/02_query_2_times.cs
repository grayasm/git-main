/*
    A Query Can Be Executed More Than Once
    Because a query defines a set of rules that are used to retrieve
    data, but does not, itself, produce results, the same query can be
    run multiple times. If the data source changes between runs, then
    the results of the query may differ. Therefore, once you define a
    query, executing it will always produce the most current results.
*/


// Create a simple query.
using System;
using System.Linq;
using System.Collections.Generic;


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

        // Change nums.
        Console.WriteLine("\nSetting nums[1] to 99.");
        nums[1] = 99;

        Console.Write("The positive values in nums after change: ");
        // Execute the query a second time.
        foreach(int i in posNums)
            Console.Write(i + " ");
        Console.WriteLine();
    }
}
