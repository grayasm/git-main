// Demonstrate Hashtable.
using System;
using System.Collections;


class HashtableDemo
{
    static void Main()
    {
        // Create a hash table.
        Hashtable ht = new Hashtable();

        // Add elements to the table.
        ht.Add("house", "Dwelling");
        ht.Add("car", "Means of transport");
        ht.Add("book", "Collection of printed words");
        ht.Add("apple", "Edible fruit");


        // Can also add by using the indexer.
        ht["tractor"] = "Farm implement";

        // Get a collection of the keys.
        ICollection c = ht.Keys;

        // Use the keys to obtain the values.
        foreach(string str in c)
            Console.WriteLine(str + ": " + ht[str]);
    }
}
