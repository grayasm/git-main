// Demonstrate several Char methods.
using System;
using System.Globalization;


class CharDemo
{
    static void Main()
    {
        string str = "This is a test. $23";
        int i;

        for(i=0; i < str.Length; i++)
        {
            Console.Write(str[i] + " is");

            if(Char.IsDigit(str[i]))
                Console.Write(" digit");

            if(Char.IsLetter(str[i]))
                Console.Write(" letter");

            if(Char.IsLower(str[i]))
                Console.Write(" lowercase");

            if(Char.IsUpper(str[i]))
                Console.Write(" uppercase");

            if(Char.IsSymbol(str[i]))
                Console.Write(" symbol");

            if(Char.IsSeparator(str[i]))
                Console.Write(" separator");

            if(Char.IsWhiteSpace(str[i]))
                Console.Write(" whitespace");

            if(Char.IsPunctuation(str[i]))
                Console.Write(" punctuation");

            Console.WriteLine();
        }

        Console.WriteLine("Original: " + str);

        // Convert to uppercase.
        string newstr = "";
        for(i=0; i < str.Length; i++)
            newstr += Char.ToUpper(str[i], CultureInfo.CurrentCulture);
        Console.WriteLine("Uppercased: " + newstr);
    }
}
