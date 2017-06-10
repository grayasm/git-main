// A closer look at Format().
using System;


class FormatDemo2
{
    static void Main()
    {
        int i;
        int sum = 0;
        int prod = 1;
        string str;

        // Display the running sum and product for the
        // numbers 1 through 10.
        for(i=1; i <= 10; i++)
        {
            sum += i;
            prod *= i;
            str = String.Format("Sum:{0,3:D} Product:{1,8:D}", sum, prod);
            Console.WriteLine(str);
        }
    }
}
