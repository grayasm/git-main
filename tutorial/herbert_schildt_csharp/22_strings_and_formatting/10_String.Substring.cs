// Use Substring().
using System;


class SubstringDemo
{
    static void Main()
    {
        string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        Console.WriteLine("str: " + str);
        Console.Write("str.Substring(15): ");

        string substr = str.Substring(15);
        Console.WriteLine(substr);
        Console.Write("str.Substring(0, 15): ");

        substr = str.Substring(0, 15);
        Console.WriteLine(substr);
    }
}
