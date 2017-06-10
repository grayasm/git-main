// Format time and date information.
using System;


class CustomTimeAndDateFormatsDemo
{
    static void Main()
    {
        DateTime dt = DateTime.Now;
        Console.WriteLine("Time is {0:hh:mm tt}", dt);
        Console.WriteLine("24 hour time is {0:HH:mm}", dt);
        Console.WriteLine("Date is {0:ddd MMM dd, yyyy}", dt);
        Console.WriteLine("Era: {0:gg}", dt);
        Console.WriteLine("Time with seconds: " + "{0:HH:mm:ss tt}", dt);
        Console.WriteLine("Use m for day of month: {0:m}", dt);
        Console.WriteLine("Use m for minutes: {0:%m}", dt);
    }
}
