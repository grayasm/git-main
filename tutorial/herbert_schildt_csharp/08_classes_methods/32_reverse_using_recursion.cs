// Display a string in reverse by using recursion.

using System;


class RevStr
{
    // Display a string backward.
    public void DisplayRev(string str)
    {
        if(str.Length > 0)
            DisplayRev(str.Substring(1, str.Length-1));
        else
            return;

        Console.Write(str[0]);
    }
}

class RevStrDemo
{
    static void Main()
    {
        string s = "this is a test";
        RevStr rsOb = new RevStr();
        Console.WriteLine("Original string: " + s);
        Console.Write("Reversed string: ");
        rsOb.DisplayRev(s);
        Console.WriteLine();
    }
}
