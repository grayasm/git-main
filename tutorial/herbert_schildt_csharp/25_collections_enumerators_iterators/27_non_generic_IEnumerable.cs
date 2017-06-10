/*
    Implementing IEnumerable and IEnumerator
    As mentioned earlier, normally it is easier (and better) to use a foreach
    loop to cycle through a collection than it is to explicitly use IEnumerator
    methods. However, understanding the operation of this interface is
    important for another reason: If you want to create a class that contains
    objects that can be enumerated via a foreach loop, then that class must
    implement IEnumerator. It must also implement IEnumerable. In other words,
    to enable an object of a class that you create to be used in a foreach loop,
    you must implement IEnumerator and IEnumerable, using either their generic
    or non-generic form. Fortunately, because these interfaces are so small,
    they are easy to implement.
*/


// Implement IEnumerable and IEnumerator.
using System;
using System.Collections;


class MyClass : IEnumerator, IEnumerable
{
    char[] chrs = { 'A', 'B', 'C', 'D' };
    int idx = -1;

    // Implement IEnumerable.
    public IEnumerator GetEnumerator()
    {
        return this;
    }

    // The following methods implement IEnumerator.
    // Return the current object.
    public object Current
    {
        get {
            return chrs[idx];
        }
    }

    // Advance to the next object.
    public bool MoveNext()
    {
        if(idx == chrs.Length-1)
        {
            Reset(); // reset enumerator at the end
            return false;
        }
        idx++;
        return true;
    }

    // Reset the enumerator to the start.
    public void Reset() { idx = -1; }
}


class EnumeratorImplDemo
{
    static void Main()
    {
        MyClass mc = new MyClass();

        // Display the contents of mc.
        foreach(char ch in mc)
            Console.Write(ch + " ");
        Console.WriteLine();

        // Display the contents of mc, again.
        foreach(char ch in mc)
            Console.Write(ch + " ");
        Console.WriteLine();
    }
}
