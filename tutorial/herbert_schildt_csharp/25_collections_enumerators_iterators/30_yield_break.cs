/*
    Stopping an Iterator
    You can stop an iterator early by using this form of the yield statement:

yield break;

*/

// Use yield break.
using System;
using System.Collections;


class MyClass
{
    char ch = 'A';

    // This iterator returns the first 10
    // letters of the alphabet.
    public IEnumerator GetEnumerator()
    {
        for(int i=0; i < 26; i++)
        {
            if(i == 10)
                yield break; // stop iterator early
            yield return (char) (ch + i);
        }
    }
}


class ItrDemo3
{
    static void Main()
    {
        MyClass mc = new MyClass();
        foreach(char ch in mc)
            Console.Write(ch + " ");
        Console.WriteLine();
    }
}
