// Sort and search an ArrayList.
using System;
using System.Collections;


class SortSearchDemo
{
    static void Main()
    {
        // Create an array list.
        ArrayList al = new ArrayList();

        // Add elements to the array list.
        al.Add(55);
        al.Add(43);
        al.Add(-4);
        al.Add(88);
        al.Add(3);
        al.Add(19);

        Console.Write("Original contents: ");
        foreach(int i in al)
            Console.Write(i + " ");

        Console.WriteLine("\n");

        // Sort
        al.Sort();

        // Use foreach loop to display the list.
        Console.Write("Contents after sorting: ");
        foreach(int i in al)
            Console.Write(i + " ");

        Console.WriteLine("\n");
        Console.WriteLine("Index of 43 is " + al.BinarySearch(43));
    }
}
