/*
    Accessing a Collection via an Enumerator
    An enumerator is an object that implements either the non-generic
    IEnumerator or the generic IEnumerator<T> interface. IEnumerator
    defines one property called Current. The non-generic version is
    shown here:

object Current { get; }

    For IEnumerator<T>, Current is declared like this:

T Current { get; }

*/

// Demonstrate an enumerator.
using System;
using System.Collections;


class EnumeratorDemo
{
    static void Main()
    {
        ArrayList list = new ArrayList(1);

        for(int i=0; i < 10; i++)
            list.Add(i);

        // Use enumerator to access list.
        IEnumerator etr = list.GetEnumerator();
        while(etr.MoveNext())
            Console.Write(etr.Current + " ");
        Console.WriteLine();

        // Re–enumerate the list.
        etr.Reset();
        while(etr.MoveNext())
             Console.Write(etr.Current + " ");
        Console.WriteLine();
    }
}
