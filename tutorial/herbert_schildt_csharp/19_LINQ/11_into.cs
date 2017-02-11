/*
    Use into to Create a Continuation
    When using select or group, you will sometimes want to generate
    a temporary result that will be used by a subsequent part of the
    query to produce the final result. This is called a query continuation
    (or just a continuation for short), and it is accomplished through
    the use of into with a select or group clause.
    It has the following general form:

into name query-body

*/

// Use into with group.
using System;
using System.Linq;


class IntoDemo
{
    static void Main()
    {
        string[] websites = { "hsNameA.com", "hsNameB.net", "hsNameC.net",
                              "hsNameD.com", "hsNameE.org", "hsNameF.org",
                              "hsNameG.tv", "hsNameH.net", "hsNameI.tv" };


        // Create a query that groups websites by top-level domain name,
        // but select only those groups that have more than two members.
        // Here, ws is the range variable over the set of groups
        // returned when the first half of the query is executed.

        var webAddrs = from addr in websites
                       where addr.LastIndexOf('.') != -1
                       group addr by addr.Substring(addr.LastIndexOf('.'))
                       into ws
                       where ws.Count() > 2
                       select ws;


        // Execute the query and display the results.
        Console.WriteLine("Top-level domains with more than 2 members.\n");
        foreach(var sites in webAddrs)
        {
            Console.WriteLine("Contents of " + sites.Key + " domain:");
            foreach(var site in sites)
                Console.WriteLine(" " + site);
            Console.WriteLine();
        }
    }
}
