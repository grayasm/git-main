// Demonstrate a SortedList.
using System;
using System.Collections;


class SLDemo
{
    static void Main()
    {
        // Create a sorted SortedList.
        SortedList sl = new SortedList();

        // Add elements to the table
        sl.Add("house", "Dwelling");
        sl.Add("car", "Means of transport");
        sl.Add("book", "Collection of printed words");
        sl.Add("apple", "Edible fruit");


        // Can also add by using the indexer.
        sl["tractor"] = "Farm implement";

        // Get a collection of the keys.
        ICollection c = sl.Keys;

        // Use the keys to obtain the values.
        Console.WriteLine("Contents of list via indexer.");
        foreach(string str in c)
            Console.WriteLine(str + ": " + sl[str]);
        Console.WriteLine();

        // Display list using integer indexes.
        Console.WriteLine("Contents by integer indexes.");
        for(int i=0; i < sl.Count; i++)
            Console.WriteLine(sl.GetByIndex(i));
        Console.WriteLine();


        // Show integer indexes of entries.
        Console.WriteLine("Integer indexes of entries.");
        foreach(string str in c)
            Console.WriteLine(str + ": " + sl.IndexOfKey(str));
    }
}
