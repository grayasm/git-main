/*
    Nesting try Blocks
    One try block can be nested within another. An exception generated
    within the inner try block that is not caught by a catch associated
    with that try is propagated to the outer try block.
*/

// Use a nested try block.

using System;


class NestTrys
{
    static void Main()
    {
        // Here, numer is longer than denom.
        int[] numer = { 4, 8, 16, 32, 64, 128, 256, 512 };
        int[] denom = { 2, 0, 4, 4, 0, 8 };

        try { // outer try
            for(int i=0; i < numer.Length; i++)
            {
                try { // nested try
                    Console.WriteLine(numer[i] + " / " + denom[i] + " is " +
                                      numer[i]/denom[i]);
                }
                catch (DivideByZeroException)
                {
                    Console.WriteLine("Can't divide by Zero!");
                }
            }
        }
        catch (IndexOutOfRangeException)
        {
            Console.WriteLine("No matching element found.");
            Console.WriteLine("Fatal error -- program terminated.");
        }
    }
}
