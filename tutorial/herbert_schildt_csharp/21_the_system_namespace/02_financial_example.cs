/*  Compute the initial investment needed to attain a known future
    value given annual rate of return and the time period in years.
 */

using System;


class InitialInvestment
{
    static void Main()
    {
        decimal initInvest; // initial investment
        decimal futVal;     // future value
        double numYears;    // number of years
        double intRate;     // annual rate of return as a decimal

        string str;
        Console.Write("Enter future value: ");
        str = Console.ReadLine();

        try
        {
            futVal = Decimal.Parse(str);
        }
        catch(FormatException exc)
        {
            Console.WriteLine(exc.Message);
            return;
        }

        Console.Write("Enter interest rate (such as 0.085): ");
        str = Console.ReadLine();

        try
        {
            intRate = Double.Parse(str);
        }
        catch(FormatException exc)
        {
            Console.WriteLine(exc.Message);
            return;
        }

        Console.Write("Enter number of years: ");
        str = Console.ReadLine();

        try
        {
            numYears = Double.Parse(str);
        }
        catch(FormatException exc)
        {
            Console.WriteLine(exc.Message);
            return;
        }


        initInvest = futVal / (decimal) Math.Pow(intRate+1.0, numYears);

        Console.WriteLine("Initial investment required: {0:C}", initInvest);
    }
}
