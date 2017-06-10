/*
    Using Iterators
    As the preceding example shows, it is not difficult to implement
    IEnumerator and IEnumerable. However, it can be made even easier
    through the use of an iterator. An iterator is a method, operator,
    or accessor that returns the members of a set of objects, one
    member at a time, from start to finish. For example, assuming some
    array that has five elements, then an iterator for that array will
    return those five elements, one at a time. Implementing an iterator
    is another way to make it possible for an object of a class to be
    used in a foreach loop.
*/

// A simple example of an iterator.
using System;
using System.Collections;


class MyClass
{
    char[] chrs = { 'A', 'B', 'C', 'D' };

    // This iterator returns the characters
    // in the chrs array.
    public IEnumerator GetEnumerator()
    {
        foreach(char ch in chrs)
            yield return ch;
    }
}


class ItrDemo
{
    static void Main()
    {
        MyClass mc = new MyClass();
        foreach(char ch in mc)
            Console.Write(ch + " ");
        Console.WriteLine();
    }
}
