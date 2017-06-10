/*
    Using finally
    Sometimes you will want to define a block of code that will execute
    when a try/catch block is left. For example, an exception might cause
    an error that terminates the current method, causing its premature
    return. However, that method may have opened a file or a network
    connection that needs to be closed. Such types of circumstances are
    common in programming, and C# provides a convenient way to handle
    them: finally. To specify a block of code to execute when a try/catch
    block is exited, include a finally block at the end of a try/catch
    sequence. The general form of a try/catch that includes finally is
    shown here:

try {
    // block of code to monitor for errors
}
catch (ExcepType1 exOb) {
    // handler for ExcepType1
}
catch (ExcepType2 exOb) {
    // handler for ExcepType2
}
finally {
    // fi nally code
}

    The finally block will be executed whenever execution leaves a
    try/catch block, no matter what conditions cause it. That is,
    whether the try block ends normally, or because of an exception,
    the last code executed is that defined by finally. The finally
    block is also executed if any code within the try block or any
    of its catch blocks returns from the method.
*/

using System;

class UseFinally
{
    public static void GenException(int what)
    {
        int t;
        int[] nums = new int[2];

        Console.WriteLine("Receiving " + what);

        try {
            switch(what) {
                case 0:
                    t = 10 / what; // generate div-by-zero error
                    break;

                case 1:
                    nums[4] = 4; // generate array index error
                    break;
                case 2:
                    return; // return from try block
            }
        }
        catch (DivideByZeroException)
        {
            Console.WriteLine("Can't divide by Zero!");
            return; // return from catch
        }
        catch (IndexOutOfRangeException)
        {
            Console.WriteLine("No matching element found.");
        }
        finally
        {
            Console.WriteLine("Leaving try.");
        }
    }
}


class FinallyDemo
{
    static void Main()
    {
        for(int i=0; i < 3; i++)
        {
            UseFinally.GenException(i);
            Console.WriteLine();
        }
    }
}
