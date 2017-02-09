// Sort on multiple criteria with orderby.
using System;
using System.Linq;


class Account
{
    public string FirstName { get; private set; }
    public string LastName { get; private set; }
    public double Balance { get; private set; }
    public string AccountNumber { get; private set; }
    public Account(string fn, string ln, string accnum, double b)
    {
        FirstName = fn;
        LastName = ln;
        AccountNumber = accnum;
        Balance = b;
    }
}


class OrderbyDemo
{
    static void Main()
    {
        // Create some data.
        Account[] accounts = { new Account("Tom", "Smith", "132CK", 100.23),
                               new Account("Tom", "Smith", "132CD", 10000.00),
                               new Account("Ralph", "Jones", "436CD", 1923.85),
                               new Account("Ralph", "Jones", "454MM", 987.132),
                               new Account("Ted", "Krammer", "897CD", 3223.19),
                               new Account("Ralph", "Jones", "434CK", -123.32),
                               new Account("Sara", "Smith", "543MM", 5017.40),
                               new Account("Sara", "Smith", "547CD", 34955.79),
                               new Account("Sara", "Smith", "843CK", 345.00),
                               new Account("Albert", "Smith", "445CK", 213.67),
                               new Account("Betty", "Krammer","968MM",5146.67),
                               new Account("Carl", "Smith", "078CD", 15345.99),
                               new Account("Jenny", "Jones", "108CK", 10.98)
                             };

        // Create a query that obtains the accounts in sorted order.
        // Sorting first by last name, then within same last names sorting by
        // by first name, and finally by account balance.
        var accInfo = from acc in accounts
                      orderby acc.LastName, acc.FirstName, acc.Balance
                      select acc;

        Console.WriteLine("Accounts in sorted order: ");
        string str = "";

        // Execute the query and display the results.
        foreach(Account acc in accInfo)
        {
            if(str != acc.FirstName)
            {
                Console.WriteLine();
                str = acc.FirstName;
            }

            Console.WriteLine("{0}, {1}\tAcc#: {2}, {3,10:C}",
                              acc.LastName, acc.FirstName,
                              acc.AccountNumber, acc.Balance);
        }
        Console.WriteLine();
    }
}
