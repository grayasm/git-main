/*
    Since version 2.0, C# has included an option that significantly simplifies
    the syntax that assigns a method to a delegate. This feature is called
    method group conversion, and it allows you to simply assign the name of
    a method to a delegate, without using new or explicitly invoking the
    delegate's constructor.
*/


using System;


// Declare a delegate type.
delegate string StrMod(string str);

class DelegateTest
{
    // Replaces spaces with hyphens.
    static string ReplaceSpaces(string s)
    {
        Console.WriteLine("Replacing spaces with hyphens.");
        return s.Replace(' ', '-');
    }

    // Remove spaces.
    static string RemoveSpaces(string s)
    {
        string temp = "";
        int i;
        Console.WriteLine("Removing spaces.");
        for(i=0; i < s.Length; i++)
            if(s[i] != ' ') temp += s[i];

        return temp;
    }

    // Reverse a string.
    static string Reverse(string s)
    {
        string temp = "";
        int i, j;

        Console.WriteLine("Reversing string.");
        for(j=0, i=s.Length-1; i >= 0; i--, j++)
            temp += s[i];

        return temp;
    }

    static void Main()
    {
        // Construct a delegate using method group conversion.
        StrMod strOp = ReplaceSpaces; // use method group conversion
        string str;

        // Call methods through the delegate.
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();

        strOp = RemoveSpaces; // use method group conversion
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();

        strOp = Reverse; // use method group conversion
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
    }
}
