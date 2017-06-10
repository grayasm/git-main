// Read a string from the keyboard, using Console.In directly.

using System;


class ReadChars2
{
    static void Main()
    {
        string str;
        Console.WriteLine("Enter some characters.");
        str = Console.In.ReadLine(); // call TextReader's ReadLine() method
        Console.WriteLine("You entered: " + str);
    }
}
