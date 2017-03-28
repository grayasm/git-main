/*
    In general, a where condition can use any valid C# expression
    that evaluates to a Boolean result.
*/

// Demonstrate another where clause.
using System;
using System.Linq;


class WhereDemo2
{
    static void Main()
    {
        string[] strs = { ".com", ".net", "hsNameA.com", "hsNameB.net",
                          "test", ".network", "hsNameC.net", "hsNameD.com" };

        // Create a query that obtains Internet addresses that
        // end with .net.
        var netAddrs = from addr in strs
                      where addr.Length > 4 && addr.EndsWith(".net",
                            StringComparison.Ordinal)
                      select addr;

        // Execute the query and display the results.
        foreach(var str in netAddrs)
            Console.WriteLine(str);
    }
}
