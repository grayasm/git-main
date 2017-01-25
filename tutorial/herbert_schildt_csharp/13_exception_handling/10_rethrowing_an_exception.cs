/*
    Rethrowing an Exception
    An exception caught by one catch can be rethrown so that it can be
    caught by an outer catch. The most likely reason for rethrowing an
    exception is to allow multiple handlers access to the exception.
    For example, perhaps one exception handler manages one aspect of
    an exception, and a second handler copes with another aspect. To
    rethrow an exception, you simply specify throw, without specifying
    an expression. That is, you use this form of throw:

throw ;

    Remember, when you rethrow an exception, it will not be recaught by
    the same catch clause. Instead, it will propagate to an outer catch.
*/

// Rethrow an exception.

using System;


class Rethrow
{
    public static void GenException()
    {
        // Here, numer is longer than denom.
        int[] numer = { 4, 8, 16, 32, 64, 128, 256, 512 };
        int[] denom = { 2, 0, 4, 4, 0, 8 };

        for(int i=0; i<numer.Length; i++)
        {
            try {
                Console.WriteLine(numer[i] + " / " + denom[i] + " is " +
                                  numer[i]/denom[i]);
            }
            catch (DivideByZeroException)
            {
                Console.WriteLine("Can't divide by Zero!");
            }
            catch (IndexOutOfRangeException)
            {
                Console.WriteLine("No matching element found.");
                throw; // rethrow the exception
            }
        }
    }
}

class RethrowDemo
{
    static void Main()
    {
        try {
            Rethrow.GenException();
        }
        catch(IndexOutOfRangeException)
        {
            // recatch exception
            Console.WriteLine("Fatal error -- " + "program terminated.");
        }
    }
}
