// Demonstrate List<T>.
using System;
using System.Collections.Generic;


class GenListDemo
{
    static void Main()
    {
        // Create a list.
        List<char> lst = new List<char>();

        Console.WriteLine("Initial number of elements: " + lst.Count);
        Console.WriteLine();
        Console.WriteLine("Adding 6 elements");

        // Add elements to the array list
        lst.Add('C');
        lst.Add('A');
        lst.Add('E');
        lst.Add('B');
        lst.Add('D');
        lst.Add('F');

        Console.WriteLine("Number of elements: " + lst.Count);

        // Display the list using array indexing.
        Console.Write("Current contents: ");

        for(int i=0; i < lst.Count; i++)
            Console.Write(lst[i] + " ");

        Console.WriteLine("\n");
        Console.WriteLine("Removing 2 elements");


        // Remove elements from the list.
        lst.Remove('F');
        lst.Remove('A');
        Console.WriteLine("Number of elements: " + lst.Count);

        // Use foreach loop to display the list.
        Console.Write("Contents: ");
        foreach(char c in lst)
            Console.Write(c + " ");

        Console.WriteLine("\n");
        Console.WriteLine("Adding 20 more elements");


        // Add enough elements to force lst to grow.
        for(int i=0; i < 20; i++)
            lst.Add((char)('a' + i));

        Console.WriteLine("Current capacity: " + lst.Capacity);
        Console.WriteLine("Number of elements after adding 20: " + lst.Count);
        Console.Write("Contents: ");

        foreach(char c in lst)
            Console.Write(c + " ");
        Console.WriteLine("\n");


        // Change contents using array indexing.
        Console.WriteLine("Change first three elements");
        lst[0] = 'X';
        lst[1] = 'Y';
        lst[2] = 'Z';
        Console.Write("Contents: ");

        foreach(char c in lst)
            Console.Write(c + " ");
        Console.WriteLine();

        // Because of generic type-safety,
        // the following line is illegal.
        // lst.Add(99); // Error, not a char!
    }
}
