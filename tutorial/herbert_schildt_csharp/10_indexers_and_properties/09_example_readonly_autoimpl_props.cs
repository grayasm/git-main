// Use read-only, auto-implemented properties for Length and Error.
// pag. 272

using System;


class FailSoftArray
{
    int[] a; // reference to underlying array

    // Construct array given its size.
    public FailSoftArray(int size)
    {
        a = new int[size];
        Length = size;
    }

    // An auto-implemented, read-only Length property.
    public int Length { get; private set; }

    // An auto-implemented, read-only Error property.
    public bool Error { get; private set; }

    // This is the indexer for FailSoftArray.
    public int this[int index]
    {
        // This is the get accessor.
        get
        {
            if(ok(index))
            {
                Error = false;
                return a[index];
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
                a[index] = value;
                Error = false;
            }
            else
                Error = true;
        }
    }

    // Return true if index is within bounds.
    private bool ok(int index)
    {
        if(index >= 0 & index < Length)
             return true;
        return false;
    }
}


// Demonstrate the improved fail-soft array.
class FinalFSDemo
{
    static void Main()
    {
        FailSoftArray fs = new FailSoftArray(5);

        // Use Error property.
        for(int i=0; i < fs.Length + 1; i++)
        {
            fs[i] = i*10;

            if(fs.Error)
                Console.WriteLine("Error with index " + i);
        }
    }
}
