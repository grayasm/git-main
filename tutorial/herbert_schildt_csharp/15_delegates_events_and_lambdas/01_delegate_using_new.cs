/*
    In straightforward language, a delegate is an object that can refer to a
    method. The general form of a delegate declaration is shown here:

delegate ret-type name(parameter-list);

    The method that will be invoked by a delegate is not determined at compile
    time, but rather at runtime.

    If you are familiar with C/C++, then it will help to know that a delegate
    in C# is similar to a function pointer in C/C++.

    A key point to understand is that a delegate can be used to call any method
    that agrees with its signature and return type. Furthermore, the method can
    be either an instance method associated with an object or a static method
    associated with a class. All that matters is that the return type and
    signature of the method agree with those of the delegate.
*/


// A simple delegate example.

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
        // Construct a delegate.
        StrMod strOp = new StrMod(ReplaceSpaces);
        string str;

        // Call methods through the delegate.
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();
        strOp = new StrMod(RemoveSpaces);
        str = strOp("This is a test.");

        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();

        strOp = new StrMod(Reverse);
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
    }
}
