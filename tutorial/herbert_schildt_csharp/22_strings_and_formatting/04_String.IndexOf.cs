// Search strings.
using System;


class StringSearchDemo
{
    static void Main()
    {
        string str = "C# has powerful string handling.";

        int idx;
        Console.WriteLine("str: " + str);
        idx = str.IndexOf('h');
        Console.WriteLine("Index of first 'h': " + idx);
        idx = str.LastIndexOf('h');
        Console.WriteLine("Index of last 'h': " + idx);


        idx = str.IndexOf("ing", StringComparison.Ordinal);
        Console.WriteLine("Index of first \"ing\": " + idx);
        idx = str.LastIndexOf("ing", StringComparison.Ordinal);
        Console.WriteLine("Index of last \"ing\": " + idx);

        char[] chrs = { 'a', 'b', 'c' };
        idx = str.IndexOfAny(chrs);
        Console.WriteLine("Index of first 'a', 'b', or 'c': " + idx);

        if(str.StartsWith("C# has", StringComparison.Ordinal))
            Console.WriteLine("str begins with \"C# has\"");
        if(str.EndsWith("ling.", StringComparison.Ordinal))
            Console.WriteLine("str ends with \"ling.\"");
    }
}
