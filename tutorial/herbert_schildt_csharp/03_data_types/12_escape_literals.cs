using System;

class Escapes
{
    static void Main()
    {
        Console.WriteLine("\a Alert (bell)");
        Console.WriteLine("\b Backspace");
        Console.WriteLine("\f Form feed");
        Console.WriteLine("\n New line (linefeed)");
        Console.WriteLine("\r Carriage return");
        Console.WriteLine("\t Horizontal tab");
        Console.WriteLine("\v Vertical tab");
        Console.WriteLine("\0 Null");
        Console.WriteLine("\' Single quote");
        Console.WriteLine("\" Double quote");
        Console.WriteLine("\\ Backslash");
    }
}