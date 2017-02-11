// Demonstrate the GroupBy() query method.
// This program reworks the earlier version that used
// the query syntax.

using System;
using System.Linq;


class GroupByDemo
{
    static void Main()
    {
        string[] websites = { "hsNameA.com", "hsNameB.net", "hsNameC.net",
                              "hsNameD.com", "hsNameE.org", "hsNameF.org",
                              "hsNameG.tv", "hsNameH.net", "hsNameI.tv" };

        // Use query methods to group websites by top-level domain name.
        var webAddrs = websites.Where(w => w.LastIndexOf('.') != –1).
                       GroupBy(x => x.Substring(x.LastIndexOf(".")));


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
