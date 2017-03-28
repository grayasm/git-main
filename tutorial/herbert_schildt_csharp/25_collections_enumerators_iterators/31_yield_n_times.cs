/*
    Using Multiple yield Directives
    You can have more than one yield statement in an iterator. However,
    each yield must return the next element in the collection. For example,
    consider this program:
*/


// Multiple yield statements are allowed.
using System;
using System.Collections;


class MyClass
{
    // This iterator returns the letters
    // A, B, C, D, and E.
    public IEnumerator GetEnumerator()
    {
        yield return 'A';
        yield return 'B';
        yield return 'C';
        yield return 'D';
        yield return 'E';
    }
}


class ItrDemo5
{
    static void Main()
    {
        MyClass mc = new MyClass();
        foreach(char ch in mc)
            Console.Write(ch + " ");
        Console.WriteLine();
    }
}
