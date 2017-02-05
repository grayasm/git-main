// Use an operator in a symbol expression.

#define EXPERIMENTAL
#define TRIAL

using System;


class Test
{
    static void Main()
    {
        #if EXPERIMENTAL
            Console.WriteLine("Compiled for experimental version.");
        #endif

        #if EXPERIMENTAL && TRIAL
            Console.Error.WriteLine("Testing experimental trial version.");
        #endif

        Console.WriteLine("This is in all versions.");
    }
}
