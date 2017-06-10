/*
    readonly
    You can create a read-only field in a class by declaring it as
    readonly. A readonly field can be given a value only by using an
    initializer when it is declared or by assigning it a value within
    a constructor. Once the value has been set, it can't be changed
    outside the constructor.
*/

// Demonstrate readonly.
using System;


class MyClass
{
    public static readonly int SIZE = 10;
}


class DemoReadOnly
{
    static void Main()
    {
        int[] source = new int[MyClass.SIZE];
        int[] target = new int[MyClass.SIZE];

        // Give source some values.
        for(int i=0; i < MyClass.SIZE; i++)
            source[i] = i;

        foreach(int i in source)
            Console.Write(i + " ");
        Console.WriteLine();


        // Reverse copy source into target.
        for(int i = MyClass.SIZE-1, j = 0; i > 0; i--, j++)
            target[j] = source[i];

        foreach(int i in target)
            Console.Write(i + " ");
        Console.WriteLine();

        // MyClass.SIZE = 100; // Error!!! can’t change
    }
}
