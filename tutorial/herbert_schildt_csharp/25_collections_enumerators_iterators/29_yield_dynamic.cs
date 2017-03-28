/*
    The term yield is a contextual keyword in the C# language. This means
    that it has special meaning only inside an iterator block. Outside of
    an iterator, yield can be used like any other identifier.
    One important point to understand is that an iterator does not need
    to be backed by an array or other type of collection. It simply must
    return the next element in a group of elements. This means the elements
    can be dynamically constructed using an algorithm.
*/

// Iterated values can be dynamically constructed.
using System;
using System.Collections;


class MyClass
{
    char ch = 'A';

    // This iterator returns the letters of the alphabet.
    public IEnumerator GetEnumerator()
    {
        for(int i=0; i < 26; i++)
            yield return (char) (ch + i);
    }
}


class ItrDemo2
{
    static void Main()
    {
        MyClass mc = new MyClass();
        foreach(char ch in mc)
            Console.Write(ch + " ");
        Console.WriteLine();
    }
}
