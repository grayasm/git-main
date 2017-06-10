// Use ToString() to format values.
using System;


class ToStringDemo
{
    static void Main()
    {
        double v = 17688.65849;
        double v2 = 0.15;
        int x = 21;

        string str = v.ToString("F2");
        Console.WriteLine(str);

        str = v.ToString("N5");
        Console.WriteLine(str);

        str = v.ToString("e");
        Console.WriteLine(str);

        str = v.ToString("r");
        Console.WriteLine(str);

        str = v2.ToString("p");
        Console.WriteLine(str);

        str = x.ToString("X");
        Console.WriteLine(str);

        str = x.ToString("D12");
        Console.WriteLine(str);

        str = 189.99.ToString("C");
        Console.WriteLine(str);
    }
}
