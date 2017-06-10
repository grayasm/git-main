/*
    More Query-Related Extension Methods
    In addition to the methods that correspond to the query keywords
    supported by C#, the .NET Framework provides several other query-related
    extension methods that are often helpful in a query. These query-related
    methods are defined for IEnumerable<T> by Enumerable.
*/

// Use several of the extension methods defined by Enumerable.
using System;
using System.Linq;


class ExtMethods
{
    static void Main()
    {
        int[] nums = { 3, 1, 2, 5, 4 };

        Console.WriteLine("The minimum value is " + nums.Min());
        Console.WriteLine("The maximum value is " + nums.Max());
        Console.WriteLine("The first value is " + nums.First());
        Console.WriteLine("The last value is " + nums.Last());
        Console.WriteLine("The sum is " + nums.Sum());
        Console.WriteLine("The average is " + nums.Average());

        if(nums.All(n => n > 0))
            Console.WriteLine("All values are greater than zero.");

        if(nums.Any(n => (n % 2) == 0))
            Console.WriteLine("At least one value is even.");

        if(nums.Contains(3))
            Console.WriteLine("The array contains 3.");
    }
}
