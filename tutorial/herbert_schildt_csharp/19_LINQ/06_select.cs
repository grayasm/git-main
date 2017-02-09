// Use select to return the square root of all positive values
// in an array of doubles.
using System;
using System.Linq;


class SelectDemo
{
    static void Main()
    {
        double[] nums = { -10.0, 16.4, 12.125, 100.85, -2.2, 25.25, -3.5 } ;

        // Create a query that returns the square roots of the
        // positive values in nums.
        var sqrRoots = from n in nums
                       where n > 0
                       select Math.Sqrt(n);

        Console.WriteLine("The square roots of the positive values" +
                          " rounded to two decimal places:");

        // Execute the query and display the results.
        foreach(double r in sqrRoots)
            Console.WriteLine("{0:#.##}", r);
    }
}
