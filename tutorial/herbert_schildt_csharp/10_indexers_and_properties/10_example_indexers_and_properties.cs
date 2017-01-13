/*
    Create a specifiable range array class.
    The RangeArray class allows indexing to begin at
    some value other than 0. When you create a RangeArray,
    you specify the beginning and ending index. Negative
    indexes are also allowed. For example, you can create
    arrays that index from -5 to 5, 1 to 10, or 50 to 56.
*/

using System;


class RangeArray
{
    // Private data.
    int[] a; // reference to underlying array

    int lowerBound; // smallest index
    int upperBound; // largest index

    // An auto-implemented, read-only Length property.
    public int Length { get; private set; }

    // An auto-implemented, read-only Error property.
    public bool Error { get; private set; }

    // Construct array given its size.
    public RangeArray(int low, int high)
    {
        high++;
        if(high <= low)
        {
            Console.WriteLine("Invalid Indices");
            high = 1; // create a minimal array for safety
            low = 0;
        }

        a = new int[high - low];
        Length = high - low;
        lowerBound = low;
        upperBound = --high;
    }

    // This is the indexer for RangeArray.
    public int this[int index]
    {
        // This is the get accessor.
        get
        {
            if(ok(index))
            {
                Error = false;
                return a[index - lowerBound];
            }
            else
            {
                Error = true;
                return 0;
            }
        }

        // This is the set accessor.
        set
        {
            if(ok(index))
            {
                a[index - lowerBound] = value;
                Error = false;
            }
            else
                Error = true;
        }
    }

    // Return true if index is within bounds.
    private bool ok(int index)
    {
        if(index >= lowerBound & index <= upperBound)
            return true;
        return false;
    }
}


// Demonstrate the index-range array.
class RangeArrayDemo
{
    static void Main()
    {
        RangeArray ra = new RangeArray(-5, 5);
        RangeArray ra2 = new RangeArray(1, 10);
        RangeArray ra3 = new RangeArray(-20, -12);

        // Demonstrate ra.
        Console.WriteLine("Length of ra: " + ra.Length);
        for(int i = -5; i <= 5; i++)
            ra[i] = i;

        Console.Write("Contents of ra: ");
        for(int i = -5; i <= 5; i++)
            Console.Write(ra[i] + " ");
        Console.WriteLine("\n");

        // Demonstrate ra2.
        Console.WriteLine("Length of ra2: " + ra2.Length);
        for(int i = 1; i <= 10; i++)
            ra2[i] = i;
        Console.Write("Contents of ra2: ");

        for(int i = 1; i <= 10; i++)
            Console.Write(ra2[i] + " ");
        Console.WriteLine("\n");

        // Demonstrate ra3.
        Console.WriteLine("Length of ra3: " + ra3.Length);
        for(int i = -20; i <= -12; i++)
            ra3[i] = i;

        Console.Write("Contents of ra3: ");
        for(int i = -20; i <= -12; i++)
             Console.Write(ra3[i] + " ");
        Console.WriteLine("\n");
    }
}
