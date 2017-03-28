// Inserting, replacing, and removing.
using System;


class InsRepRevDemo
{
    static void Main()
    {
        string str = "This test";
        Console.WriteLine("Original string: " + str);

        // Insert
        str = str.Insert(5, "is a ");
        Console.WriteLine(str);

        // Replace string
        str = str.Replace("is", "was");
        Console.WriteLine(str);

        // Replace characters
        str = str.Replace('a', 'X');
        Console.WriteLine(str);

        // Remove
        str = str.Remove(4, 5);
        Console.WriteLine(str);
    }
}
