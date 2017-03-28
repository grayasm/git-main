/*
    Interface Indexers
    An interface can specify an indexer. A simple one-dimensional indexer
    declared in an interface has this general form:

// interface indexer
element-type this[int index] {
    get;
    set;
}

    As before, only get or set will be present for read-only or write-only
    indexers, respectively. Also, no access modifiers are allowed on the
    accessors when an indexer is declared in an interface.
*/

// Add an indexer in an interface.

using System;


public interface ISeries
{
    // An interface property.
    int Next
    {
        get; // return the next number in series
        set; // set next number
    }

    // An interface indexer.
    int this[int index]
    {
        get; // return the specified number in series
    }
}


// Implement ISeries.
class ByTwos : ISeries
{
    int val;

    public ByTwos()
    {
        val = 0;
    }

    // Get or set value using a property.
    public int Next
    {
        get {
            val += 2;
            return val;
        }

        set {
            val = value;
        }
    }

    // Get a value using an index.
    public int this[int index]
    {
        get {
            val = 0;
            for(int i=0; i < index; i++)
                val += 2;

            return val;
        }
    }
}


// Demonstrate an interface indexer.
class SeriesDemo4
{
    static void Main()
    {
        ByTwos ob = new ByTwos();

        // Access series through a property.
        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob.Next);

        Console.WriteLine("\nStarting at 21");
        ob.Next = 21;

        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob.Next);

        Console.WriteLine("\nResetting to 0");
        ob.Next = 0;

        // Access series through an indexer.
        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob[i]);
    }
}
