// Use String.Format() to format a value.
using System;


class FormatDemo
{
    static void Main()
    {
        double v = 17688.65849;
        double v2 = 0.15;
        int x = 21;

        string str = String.Format("{0:F2}", v);
        Console.WriteLine(str);

        str = String.Format("{0:N5}", v);
        Console.WriteLine(str);

        str = String.Format("{0:e}", v);
        Console.WriteLine(str);

        str = String.Format("{0:r}", v);
        Console.WriteLine(str);

        str = String.Format("{0:p}", v2);
        Console.WriteLine(str);

        str = String.Format("{0:X}", x);
        Console.WriteLine(str);

        str = String.Format("{0:D12}", x);
        Console.WriteLine(str);

        str = String.Format("{0:C}", 189.99);
        Console.WriteLine(str);
    }
}
