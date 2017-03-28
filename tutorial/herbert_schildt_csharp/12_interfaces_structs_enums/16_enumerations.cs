/*
    Enumerations
    An enumeration is a set of named integer constants. The keyword enum
    declares an enumerated type.
    The general form for an enumeration is:

enum name { enumeration list };

    A key point to understand about an enumeration is that each of the
    symbols stands for an integer value. However, no implicit conversions
    are defined between an enum type and the built-in integer types, so an
    explicit cast must be used. Also, a cast is required when converting
    between two enumeration types. Since enumerations represent integer values,
    you can use an enumeration to control a switch statement or as the control
    variable in a for loop, for example.

    Each enumeration symbol is given a value one greater than the symbol
    that precedes it. By default, the value of the first enumeration
    symbol is 0.
*/


// Demonstrate an enumeration.

using System;


class EnumDemo
{
    enum Apple { Jonathan, GoldenDel, RedDel, Winesap, Cortland, McIntosh };

    static void Main()
    {
        string[] color = {
                           "Red",
                           "Yellow",
                           "Red",
                           "Red",
                           "Red",
                           "Reddish Green"
                         };

        Apple i; // declare an enum variable

        // Use i to cycle through the enum.
        for(i = Apple.Jonathan; i <= Apple.McIntosh; i++)
            Console.WriteLine(i + " has value of " + (int)i);
        Console.WriteLine();

        // Use an enumeration to index an array.
        for(i = Apple.Jonathan; i <= Apple.McIntosh; i++)
            Console.WriteLine("Color of " + i + " is " + color[(int)i]);
    }
}
