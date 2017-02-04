/*
    In simple terms, multicasting is the ability to create an invocation
    list, or chain, of methods that will be automatically called when a
    delegate is invoked.

    Such a chain is very easy to create. Simply instantiate a delegate, and
    then use the + or += operator to add methods to the chain.
    To remove a method, use – or – =.

    If the delegate returns a value, then the value returned by the last
    method in the list becomes the return value of the entire delegate
    invocation. Thus, a delegate that makes use of multicasting will often
    have a void return type.
*/

// Demonstrate multicasting.

using System;


// Declare a delegate type.
delegate void StrMod(ref string str);

class MultiCastDemo
{
    // Replaces spaces with hyphens.
    static void ReplaceSpaces(ref string s)
    {
        Console.WriteLine("Replacing spaces with hyphens.");
        s = s.Replace(' ', '-');
    }

    // Remove spaces.
    static void RemoveSpaces(ref string s)
    {
        string temp = "";
        int i;

        Console.WriteLine("Removing spaces.");
        for(i=0; i < s.Length; i++)
            if(s[i] != ' ')
                temp += s[i];

        s = temp;
    }

    // Reverse a string.
    static void Reverse(ref string s)
    {
        string temp = "";
        int i, j;

        Console.WriteLine("Reversing string.");
        for(j=0, i=s.Length-1; i >= 0; i--, j++)
            temp += s[i];

        s = temp;
    }


    static void Main()
    {
        // Construct delegates.
        StrMod strOp;
        StrMod replaceSp = ReplaceSpaces;
        StrMod removeSp = RemoveSpaces;
        StrMod reverseStr = Reverse;
        string str = "This is a test";

        // Set up multicast.
        strOp = replaceSp;
        strOp += reverseStr;

        // Call multicast.
        strOp(ref str);
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();

        // Remove replace and add remove.
        strOp -= replaceSp;
        strOp += removeSp;
        str = "This is a test."; // reset string

        // Call multicast.
        strOp(ref str);
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();
    }
}
