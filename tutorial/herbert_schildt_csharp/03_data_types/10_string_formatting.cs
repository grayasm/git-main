using System;

// WriteLine(“format string”, arg0, arg1, ... , argN);

class Formatting
{
    static void Main()
    {
        Console.WriteLine("You ordered " + 2 + " items at $" + 3 + " each.");

        Console.WriteLine("Here is 10/3: " + 10.0/3.0);

        Console.WriteLine("February has {0} or {1} days.", 28, 29);

        Console.WriteLine("February has {0,10} or {1,5} days.", 28, 29);

        Console.WriteLine("Here is 10/3: {0:#.##}", 10.0/3.0);

        Console.WriteLine("{0:###,###.##}", 123456.56);

        decimal balance;
        balance = 12323.09m;
        Console.WriteLine("Current balance is {0:C}", balance);

        decimal price;
        decimal discount;
        decimal discounted_price;
        // Compute discounted price.
        price = 19.95m;
        discount = 0.15m; // discount rate is 15%
        discounted_price = price - ( price * discount);
        Console.WriteLine("Discounted price: {0:C}", discounted_price);

        int i;
        Console.WriteLine("Value\tSquared\tCubed");
        for(i = 1; i < 10; i++)
              Console.WriteLine("{0}\t{1}\t{2}", i, i*i, i*i*i);

    }
}
