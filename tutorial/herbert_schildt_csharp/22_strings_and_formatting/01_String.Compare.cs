// Demonstrate string comparisons.
using System;


class CompareDemo
{
    static void Main()
    {
        string str1 = "alpha";
        string str2 = "Alpha";
        string str3 = "Beta";
        string str4 = "alpha";
        string str5 = "alpha, beta";
        int result;

        // First, demonstrate the differences between culture-sensitive
        // and ordinal comparison.
        result = String.Compare(str1, str2, StringComparison.CurrentCulture);
        Console.Write("Using a culture-sensitive comparison: ");
        if(result < 0)
        Console.WriteLine(str1 + " is less than " + str2);
        else if(result > 0)
        Console.WriteLine(str1 + " is greater than " + str2);
        else
        Console.WriteLine(str1 + " equals " + str2);


        result = String.Compare(str1, str2, StringComparison.Ordinal);
        Console.Write("Using an ordinal comparison: ");
        if(result < 0)
        Console.WriteLine(str1 + " is less than " + str2);
        else if(result > 0)
        Console.WriteLine(str1 + " is greater than " + str2);
        else
        Console.WriteLine(str1 + " equals " + str4);


        // Use the CompareOrdinal() method.
        result = String.CompareOrdinal(str1, str2);
        Console.Write("Using CompareOrdinal(): ");
        if(result < 0)
        Console.WriteLine(str1 + " is less than " + str2);
        else if(result > 0)
        Console.WriteLine(str1 + " is greater than " + str2);
        else
        Console.WriteLine(str1 + " equals " + str4);
        Console.WriteLine();


        // Use == to determine if two strings are equal.
        // This comparison is ordinal.
        if(str1 == str4) Console.WriteLine(str1 + " == " + str4);

        // Use != on strings.
        if(str1 != str3) Console.WriteLine(str1 + " != " + str3);
        if(str1 != str2) Console.WriteLine(str1 + " != " + str2);
        Console.WriteLine();


        // Use Equals() to perform an ordinal, case-insensitive comparison.
        if(String.Equals(str1, str2, StringComparison.OrdinalIgnoreCase))
        Console.WriteLine("Using Equals() with OrdinalIgnoreCase, " +
        str1 + " equals " + str2);
        Console.WriteLine();


        // Compare a portion of a string.
        if(String.Compare(str2, 0, str5, 0, 3,
        StringComparison.CurrentCulture) > 0)
        {
            Console.WriteLine("Using the current culture, the first " +
                              "3 characters of " + str2 +
                              "\nare greater than the first " +
                              "3 characters of " + str5);
        }
    }
}
