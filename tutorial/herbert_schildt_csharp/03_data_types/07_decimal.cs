// Use the decimal type to compute a discount.

using System;

class Example
{
    static void UseDecimal()
    {
        decimal price;
        decimal discount;
        decimal discounted_price;

        // Compute discounted price.
        price = 19.95m;
        discount = 0.15m; // discount rate is 15%
        discounted_price = price - ( price * discount);

        Console.WriteLine("Discounted price: $" + discounted_price);
    }

    /*
        Use the decimal type to compute the future value
        of an investment.
    */
    static void FutVal()
    {
        decimal amount;
        decimal rate_of_return;
        int years, i;

        amount = 1000.0M;
        rate_of_return = 0.07M;
        years = 10;

        Console.WriteLine("Original investment: $" + amount);
        Console.WriteLine("Rate of return: " + rate_of_return);
        Console.WriteLine("Over " + years + " years");

        for(i = 0; i < years; i++)
              amount = amount + (amount * rate_of_return);

        Console.WriteLine("Future value is $" + amount);
    }

    static void Main()
    {
        UseDecimal();
        FutVal();
    }
}