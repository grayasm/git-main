/*
    Is object a Universal Data Type?
    Given that object is a base class for all other types and that boxing
    of the value types takes place automatically, it is possible to use
    object as a "universal" data type.
*/

// Use object to create a "generic" array.

using System;


class GenericDemo
{
    static void Main()
    {
        object[] ga = new object[10];

        // Store ints.
        for(int i=0; i < 3; i++)
            ga[i] = i;

        // Store doubles.
        for(int i=3; i < 6; i++)
            ga[i] = (double) i / 2;

        // Store two strings, a bool, and a char.
        ga[6] = "Hello";
        ga[7] = true;
        ga[8] = 'X';
        ga[9] = "end";


        for(int i = 0; i < ga.Length; i++)
            Console.WriteLine("ga[" + i + "]: " + ga[i] + " ");
    }
}
