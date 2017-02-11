/*
    Create Queries by Using the Query Methods
    By using the query methods in conjunction with lambda expressions,
    it is possible to create queries that do not use the C# query syntax.
    Instead, the query methods are called. Let’s begin with a simple example.
    It reworks the first program in this chapter so that it uses calls
    to Where( ) and Select( ) rather than the query keywords.
*/


// Use the query methods to create a simple query.
// This is a reworked version of the first program in this chapter.
using System;
using System.Linq;


class SimpQuery
{
    static void Main()
    {
        int[] nums = { 1, -2, 3, 0, -4, 5 };

        // Use Where() and Select() to create a simple query.
        var posNums = nums.Where(n => n > 0).Select(r => r);

        Console.Write("The positive values in nums: ");
        // Execute the query and display the results.
        foreach(int i in posNums)
            Console.Write(i + " ");
        Console.WriteLine();
    }
}
