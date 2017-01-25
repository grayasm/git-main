// Write to Console.Out and Console.Error.

using System;


class ErrOut
{
    static void Main()
    {
        int a=10, b=0;
        int result;

        Console.Out.WriteLine("This will generate an exception.");

        try
        {
            result = a / b; // generate an exception
        }
        catch(DivideByZeroException exc)
        {
            Console.Error.WriteLine(exc.Message);
        }
    }
}
