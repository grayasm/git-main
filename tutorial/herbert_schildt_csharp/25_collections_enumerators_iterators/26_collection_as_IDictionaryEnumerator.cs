// Demonstrate IDictionaryEnumerator.
using System;
using System.Collections;


class IDicEnumDemo
{
    static void Main()
    {
        // Create a hash table.
        Hashtable ht = new Hashtable();

        // Add elements to the table.
        ht.Add("Tom", "555–3456");
        ht.Add("Mary", "555–9876");
        ht.Add("Todd", "555–3452");
        ht.Add("Ken", "555–7756");

        // Demonstrate enumerator.
        IDictionaryEnumerator etr = ht.GetEnumerator();
        Console.WriteLine("Display info using Entry.");
        while(etr.MoveNext())
            Console.WriteLine(etr.Entry.Key + ": " + etr.Entry.Value);
        Console.WriteLine();

        Console.WriteLine("Display info using Key and Value directly.");
        etr.Reset();
        while(etr.MoveNext())
            Console.WriteLine(etr.Key + ": " + etr.Value);
    }
}
