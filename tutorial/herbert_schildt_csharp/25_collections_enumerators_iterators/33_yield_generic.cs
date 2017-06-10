/*
    Creating a Generic Iterator
    The preceding examples of iterators have been non-generic, but it is,
    of course, also possible to create generic iterators. Doing so is
    quite easy: Simply return an object of the generic IEnumerator<T> or
    IEnumerable<T> type.
    Here is an example that creates a generic iterator:
*/


// A simple example of a generic iterator.
using System;
using System.Collections.Generic;


class MyClass<T>
{
    T[] array;

    public MyClass(T[] a)
    {
        array = a;
    }

    // This iterator returns the characters
    // in the chrs array.
    public IEnumerator<T> GetEnumerator()
    {
        foreach(T obj in array)
            yield return obj;
    }
}


class GenericItrDemo
{
    static void Main()
    {
        int[] nums = { 4, 3, 6, 4, 7, 9 };

        MyClass<int> mc = new MyClass<int>(nums);
        foreach(int x in mc)
            Console.Write(x + " ");
        Console.WriteLine();

        bool[] bVals = { true, true, false, true };

        MyClass<bool> mc2 = new MyClass<bool>(bVals);
        foreach(bool b in mc2)
            Console.Write(b + " ");
        Console.WriteLine();
    }
}
