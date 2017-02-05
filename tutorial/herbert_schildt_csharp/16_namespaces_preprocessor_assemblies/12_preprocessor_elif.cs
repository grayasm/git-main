// Demonstrate #elif.

#define RELEASE

using System;


class Test
{
    static void Main()
    {
        #if EXPERIMENTAL
            Console.WriteLine("Compiled for experimental version.");
        #elif RELEASE
            Console.WriteLine("Compiled for release.");
        #else
            Console.WriteLine("Compiled for internal testing.");
        #endif

        #if TRIAL && !RELEASE
            Console.WriteLine("Trial version.");
        #endif

        Console.WriteLine("This is in all versions.");
    }
}
