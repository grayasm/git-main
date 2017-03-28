/*
    Creating a Named Iterator
    Although the preceding examples have shown the easiest way to
    implement an iterator, there is an alternative: the named iterator.
    In this approach, you create a method, operator, or accessor that
    returns a reference to an IEnumerable object. Your code will use
    this object to supply the iterator. A named iterator is a method
    with the following general form:

public IEnumerable itr-name(param-list) {
    // ...
    yield return obj;
}

*/

// Use named iterators.
using System;
using System.Collections;


class MyClass
{
    char ch = 'A';

    // This iterator returns the letters
    // of the alphabet, beginning at A and
    // stopping at the specified stopping point.

    public IEnumerable MyItr(int end)
    {
        for(int i=0; i < end; i++)
            yield return (char) (ch + i);
    }

    // This iterator returns the specified
    // range of letters.
    public IEnumerable MyItr(int begin, int end)
    {
        for(int i=begin; i < end; i++)
            yield return (char) (ch + i);
    }
}


class ItrDemo4
{
    static void Main()
    {
        MyClass mc = new MyClass();

        Console.WriteLine("Iterate the first 7 letters:");
        foreach(char ch in mc.MyItr(7))
            Console.Write(ch + " ");
        Console.WriteLine("\n");


        Console.WriteLine("Iterate letters from F to L:");
        foreach(char ch in mc.MyItr(5, 12))
            Console.Write(ch + " ");
        Console.WriteLine();
    }
}
