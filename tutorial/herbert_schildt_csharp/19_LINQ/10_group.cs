/*
    Group Results with group
    One of the most powerful query features is provided by the group
    clause because it enables you to create results that are grouped
    by keys. Using the sequence obtained from a group, you can easily
    access all of the data associated with a key. This makes group an
    easy and effective way to retrieve data that is organized into
    sequences of related items. The group clause is one of only two
    clauses that can end a query. (The other is select.)
    The group clause has the following general form:

group range-variable by key

*/

// Demonstrate the group clause.
using System;
using System.Linq;


class GroupDemo
{
    static void Main()
    {
        string[] websites = { "hsNameA.com", "hsNameB.net", "hsNameC.net",
                              "hsNameD.com", "hsNameE.org", "hsNameF.org",
                              "hsNameG.tv", "hsNameH.net", "hsNameI.tv" };

        // Create a query that groups websites by top-level domain name.
        var webAddrs = from addr in websites
                       where addr.LastIndexOf('.') != -1
                       group addr by addr.Substring(addr.LastIndexOf('.'));

        // Execute the query and display the results.
        foreach(var sites in webAddrs)
        {
            Console.WriteLine("Web sites grouped by " + sites.Key);
            foreach(var site in sites)
                Console.WriteLine(" " + site);
            Console.WriteLine();
        }
    }
}
