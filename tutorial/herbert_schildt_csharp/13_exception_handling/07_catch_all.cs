/*
    Catching All Exceptions
    Occasionally, you might want to catch all exceptions, no matter the type.
    To do this, use a catch clause that specifies no exception type or variable.
    It has this general form:

catch {
    // handle exceptions
}

    This creates a “catch all” handler that ensures that all exceptions
    are caught by your program.
*/


// Use the "catch all" catch.

using System;


class ExcDemo5
{
    static void Main()
    {
        // Here, numer is longer than denom.
        int[] numer = { 4, 8, 16, 32, 64, 128, 256, 512 };
        int[] denom = { 2, 0, 4, 4, 0, 8 };

        for(int i=0; i < numer.Length; i++)
        {
            try
            {
                Console.WriteLine(numer[i] + " / " + denom[i] + " is " +
                                  numer[i]/denom[i]);
            }
            catch    // A "catch-all" catch.
            {
                Console.WriteLine("Some exception occurred.");
            }
        }
    }
}
