// Demonstrate Contains().
using System;


class ContainsDemo
{
    static void Main()
    {
        string str = "C# combines power with performance.";
        if(str.Contains("power"))
            Console.WriteLine("The sequence power was found.");

        if(str.Contains("pow"))
            Console.WriteLine("The sequence pow was found.");

        if(!str.Contains("powerful"))
            Console.WriteLine("The sequence powerful was not found.");
    }
}
