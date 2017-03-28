// Demonstrate #else.

#define EXPERIMENTAL

using System;


class Test
{
    static void Main()
    {
        #if EXPERIMENTAL
            Console.WriteLine("Compiled for experimental version.");
        #else
            Console.WriteLine("Compiled for release.");
        #endif

        #if EXPERIMENTAL && TRIAL
            Console.Error.WriteLine("Testing experimental trial version.");
        #else
            Console.Error.WriteLine("Not experimental trial version.");
        #endif

        Console.WriteLine("This is in all versions.");
    }
}
