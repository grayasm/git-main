/*
    Throwing an Exception
    The preceding examples have been catching exceptions generated
    automatically by the runtime system. However, it is possible to
    throw an exception manually by using the throw statement.
    Its general form is shown here:

throw exceptOb;

    The exceptOb must be an object of an exception class derived from Exception.
*/

// Manually throw an exception.

using System;


class ThrowDemo
{
    static void Main()
    {
        try {
            Console.WriteLine("Before throw.");
            throw new DivideByZeroException();
        }
        catch (DivideByZeroException)
        {
            Console.WriteLine("Exception caught.");
        }

        Console.WriteLine("After try/catch statement.");
    }
}
