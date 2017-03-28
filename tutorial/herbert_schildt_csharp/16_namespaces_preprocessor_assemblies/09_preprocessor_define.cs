// Demonstrate #if, #endif, and #define.

#define EXPERIMENTAL

using System;


class Test
{
    static void Main()
    {
        #if EXPERIMENTAL
            Console.WriteLine("Compiled for experimental version.");
        #endif

        Console.WriteLine("This is in all versions.");
    }
}
