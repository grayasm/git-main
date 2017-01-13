/*
    Indexers
    As you know, array indexing is performed using the [ ] operator.
    It is possible to define the [ ] operator for classes that you create,
    but you don’t use an operator method. Instead, you create an indexer.

    An indexer allows an object to be indexed like an array. The main use of
    indexers is to support the creation of specialized arrays that are subject
    to one or more constraints. However, you can use an indexer for any purpose
    for which an array-like syntax is beneficial. Indexers can have one or more
    dimensions. We will begin with onedimensional indexers.

    Creating One-Dimensional Indexers
    A simple one-dimensional indexer has this general form:

    element-type this[int index]
    {
       // The get accessor
       get
       {
           // return the value specifi ed by index
       }

       // The set accessor
       set
       {
           // set the value specifi ed by index
       }
    }


    Here, element-type is the element type of the indexer. Thus, each element
    accessed by the indexer will be of type element-type. This type corresponds
    to the element type of an array. The parameter index receives the index of
    the element being accessed. Technically, this parameter does not have to be
    of type int, but since indexers are typically used to provide array
    indexing, using an integer type is quite common.

    Inside the body of the indexer two accessors are defined that are called
    get and set. An accessor is similar to a method except that it does not
    declare a return type or parameters. The accessors are automatically called
    when the indexer is used, and both accessors receive index as a parameter.
    If the indexer is on the left side of an assignment statement, then the
    set accessor is called and the element specified by index must be set.
    Otherwise, the get accessor is called and the value associated with index
    must be returned. The set method also receives an implicit parameter called
    value, which contains the value being assigned to the specified index.
    One of the benefits of an indexer is that you can control precisely how an
    array is accessed, heading off improper access.
*/


// Use an indexer to create a fail-soft array.

using System;


class FailSoftArray
{
    int[] a; // reference to underlying array
    public int Length; // Length is public
    public bool ErrFlag; // indicates outcome of last operation

    // Construct array given its size.
    public FailSoftArray(int size)
    {
        a = new int[size];
        Length = size;
    }

    // This is the indexer for FailSoftArray.
    public int this[int index]
    {
        // This is the get accessor.
        get
        {
            if(ok(index))
            {
                ErrFlag = false;
                return a[index];
            }
            else
            {
                ErrFlag = true;
                return 0;
            }
        }

        // This is the set accessor.
        set
        {
            if(ok(index))
            {
                a[index] = value;
                ErrFlag = false;
            }
            else
                ErrFlag = true;
        }
    }


    // Return true if index is within bounds.
    private bool ok(int index)
    {
        if(index >= 0 & index < Length) return true;
        return false;
    }
}

// Demonstrate the fail-soft array.
class FSDemo
{
    static void Main()
    {
        FailSoftArray fs = new FailSoftArray(5);
        int x;

        // Show quiet failures.
        Console.WriteLine("Fail quietly.");

        for(int i=0; i < (fs.Length * 2); i++)
            fs[i] = i*10;

        for(int i=0; i < (fs.Length * 2); i++)
        {
            x = fs[i];
            if(x != -1) Console.Write(x + " ");
        }

        Console.WriteLine();
        // Now, display failures.
        Console.WriteLine("\nFail with error reports.");
        for(int i=0; i < (fs.Length * 2); i++)
        {
            fs[i] = i*10;
            if(fs.ErrFlag)
                Console.WriteLine("fs[" + i + "] out-of-bounds");
        }

        for(int i=0; i < (fs.Length * 2); i++)
        {
            x = fs[i];
            if(!fs.ErrFlag)
                Console.Write(x + " ");
            else
                Console.WriteLine("fs[" + i + "] out-of-bounds");
        }
    }
}
