// Read a character from the keyboard.

using System;


class KbIn
{
    static void Main()
    {
        char ch;
        Console.Write("Press a key followed by ENTER: ");
        ch = (char) Console.Read(); // get a char
        Console.WriteLine("Your key is: " + ch);
    }
}
