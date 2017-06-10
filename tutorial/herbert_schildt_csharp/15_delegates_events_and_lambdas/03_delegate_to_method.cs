// Delegates can refer to instance methods, too.

using System;


// Declare a delegate type.
delegate string StrMod(string str);

class StringOps
{
    // Replaces spaces with hyphens.
    public string ReplaceSpaces(string s)
    {
        Console.WriteLine("Replacing spaces with hyphens.");
        return s.Replace(' ', '-');
    }

    // Remove spaces.
    public string RemoveSpaces(string s)
    {
        string temp = "";
        int i;

        Console.WriteLine("Removing spaces.");
        for(i=0; i < s.Length; i++)
            if(s[i] != ' ')
                temp += s[i];

        return temp;
    }

    // Reverse a string.
    public string Reverse(string s)
    {
        string temp = "";
        int i, j;

        Console.WriteLine("Reversing string.");
        for(j=0, i=s.Length-1; i >= 0; i--, j++)
            temp += s[i];

        return temp;
    }
}


class DelegateTest
{
    static void Main()
    {
        StringOps so = new StringOps(); // create an instance of StringOps

        // Initialize a delegate.
        StrMod strOp = so.ReplaceSpaces;
        string str;

        // Call methods through delegates.
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();

        strOp = so.RemoveSpaces;
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();

        strOp = so.Reverse;
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
    }
}
