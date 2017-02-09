// Return a portion of the range variable.
using System;
using System.Linq;


class EmailAddress
{
    public string Name { get; set; }
    public string Address { get; set; }
    public EmailAddress(string n, string a)
    {
        Name = n;
        Address = a;
    }
}


class SelectDemo2
{
    static void Main()
    {
        EmailAddress[] addrs = {
                        new EmailAddress("Herb", "Herb@HerbSchildt.com"),
                        new EmailAddress("Tom", "Tom@HerbSchildt.com"),
                        new EmailAddress("Sara", "Sara@HerbSchildt.com")
                       };

        // Create a query that selects e-mail addresses.
        var eAddrs = from entry in addrs
                     select entry.Address;

        Console.WriteLine("The e-mail addresses are");
        // Execute the query and display the results.
        foreach(string s in eAddrs)
            Console.WriteLine(" " + s);
    }
}
