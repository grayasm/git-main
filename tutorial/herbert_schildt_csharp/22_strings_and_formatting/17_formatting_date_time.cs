// Format time and date information.
using System;


class TimeAndDateFormatDemo
{
    static void Main()
    {
        DateTime dt = DateTime.Now; // obtain current time
        Console.WriteLine("d format: {0:d}", dt);
        Console.WriteLine("D format: {0:D}", dt);
        Console.WriteLine("t format: {0:t}", dt);
        Console.WriteLine("T format: {0:T}", dt);
        Console.WriteLine("f format: {0:f}", dt);
        Console.WriteLine("F format: {0:F}", dt);
        Console.WriteLine("g format: {0:g}", dt);
        Console.WriteLine("G format: {0:G}", dt);
        Console.WriteLine("m format: {0:m}", dt);
        Console.WriteLine("M format: {0:M}", dt);
        Console.WriteLine("o format: {0:o}", dt);
        Console.WriteLine("O format: {0:O}", dt);
        Console.WriteLine("r format: {0:r}", dt);
        Console.WriteLine("R format: {0:R}", dt);
        Console.WriteLine("s format: {0:s}", dt);
        Console.WriteLine("u format: {0:u}", dt);
        Console.WriteLine("U format: {0:U}", dt);
        Console.WriteLine("y format: {0:y}", dt);
        Console.WriteLine("Y format: {0:Y}", dt);
    }
}
