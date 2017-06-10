// The first delegate example rewritten to use
// statement lambdas.

using System;


// Declare a delegate type.
delegate string StrMod(string s);


class UseStatementLambdas
{
    static void Main()
    {
        // Create delegates that refer to lambda expressions
        // that perform various string modifications.
        // Replaces spaces with hyphens.

        StrMod ReplaceSpaces = s => {

            Console.WriteLine("Replacing spaces with hyphens.");
            return s.Replace(' ', '-');
        };

        // Remove spaces.

        StrMod RemoveSpaces = s => {

            string temp = "";
            int i;

            Console.WriteLine("Removing spaces.");
            for(i=0; i < s.Length; i++)
                if(s[i] != ' ')
                    temp += s[i];

            return temp;
        };

        // Reverse a string.

        StrMod Reverse = s => {

            string temp = "";
            int i, j;

            Console.WriteLine("Reversing string.");

            for(j=0, i=s.Length-1; i >= 0; i--, j++)
                temp += s[i];

            return temp;
        };

        string str;

        // Call methods through the delegate.
        StrMod strOp = ReplaceSpaces;
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();


        strOp = RemoveSpaces;
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
        Console.WriteLine();

        strOp = Reverse;
        str = strOp("This is a test.");
        Console.WriteLine("Resulting string: " + str);
    }
}
