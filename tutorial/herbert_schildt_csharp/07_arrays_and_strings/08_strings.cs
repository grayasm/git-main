using System;
using System.Globalization;


class StringDemo
{
    static void Main()
    {

        // Introduce string.
        char[] charray = {'A', ' ', 's', 't', 'r', 'i', 'n', 'g', '.' };
        string str1i = new string(charray);
        string str2i = "Another string.";
        Console.WriteLine(str1i);
        Console.WriteLine(str2i);



        // Some string operations.
        string str1 = "When it comes to .NET programming, C# is #1.";
        string str2 = "When it comes to .NET programming, C# is #1.";
        string str3 = "C# strings are powerful.";

        string strUp, strLow;
        int result, idx;

        Console.WriteLine("str1: " + str1);
        Console.WriteLine("Length of str1: " + str1.Length);

        // Create upper- and lowercase versions of str1.
        strLow = str1.ToLower(CultureInfo.CurrentCulture);
        strUp = str1.ToUpper(CultureInfo.CurrentCulture);
        Console.WriteLine("Lowercase version of str1:\n " + strLow);
        Console.WriteLine("Uppercase version of str1:\n " + strUp);

        Console.WriteLine();


        // Display str1, one char at a time.
        Console.WriteLine("Display str1, one char at a time.");
        for(int i=0; i < str1.Length; i++)
             Console.Write(str1[i]);

        Console.WriteLine("\n");

        // Compare strings using == and !=. These comparisons are ordinal.
        if(str1 == str2)
            Console.WriteLine("str1 == str2");
        else
            Console.WriteLine("str1 != str2");

        if(str1 == str3)
            Console.WriteLine("str1 == str3");
        else
            Console.WriteLine("str1 != str3");

        // This comparison is culture-sensitive.
        result = string.Compare(str1, str3, StringComparison.CurrentCulture);
        if(result == 0)
            Console.WriteLine("str1 and str3 are equal");
        else if(result < 0)
            Console.WriteLine("str1 is less than str3");
        else
            Console.WriteLine("str1 is greater than str3");

        Console.WriteLine();

        // Assign a new string to str2.
        str2 = "One Two Three One";

        // Search a string.
        idx = str2.IndexOf("One", StringComparison.Ordinal);
        Console.WriteLine("Index of first occurrence of One: " + idx);
        idx = str2.LastIndexOf("One", StringComparison.Ordinal);
        Console.WriteLine("Index of last occurrence of One: " + idx);


        // Demonstrate string arrays.
        string[] str = { "This", "is", "a", "test." };
        Console.WriteLine("Original array: ");

        for(int i=0; i < str.Length; i++)
            Console.Write(str[i] + " ");

        Console.WriteLine("\n");

        // Change a string.
        str[1] = "was";
        str[3] = "test, too!";
        Console.WriteLine("Modified array: ");

        for(int i=0; i < str.Length; i++)
            Console.Write(str[i] + " ");


        // Display the digits of an integer using words.
        int num;
        int nextdigit;
        int numdigits;
        int[] n = new int[20];
        string[] digits = { "zero", "one", "two",
                            "three", "four", "five",
                            "six", "seven", "eight",
                            "nine" };

        num = 1908;

        Console.WriteLine("Number: " + num);
        Console.Write("Number in words: ");

        nextdigit = 0;
        numdigits = 0;


        // Get individual digits and store in n.
        // These digits are stored in reverse order.
        do
        {
            nextdigit = num % 10;
            n[numdigits] = nextdigit;
            numdigits++;
            num = num / 10;
        } while(num > 0);

        numdigits--;

        // Display the words.
        for( ; numdigits >= 0; numdigits--)
            Console.Write(digits[n[numdigits]] + " ");

        Console.WriteLine();

        //Strings Are Immutable
        string orgstr = "C# makes strings easy.";

        // Construct a substring.
        string substr = orgstr.Substring(5, 12);
        Console.WriteLine("orgstr: " + orgstr);
        Console.WriteLine("substr: " + substr);


        // A string can control a switch statement.
        string[] strs = { "one", "two", "three", "two", "one" };
        foreach(string s in strs)
        {
            switch(s)
            {
            case "one":
                Console.Write(1);
                break;

            case "two":
                Console.Write(2);
                break;

            case "three":
                Console.Write(3);
                break;
            }
        }

        Console.WriteLine();
    }
}