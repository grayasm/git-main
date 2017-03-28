/*
    Exception-Handling Fundamentals
    C# exception handling is managed via four keywords:
        try, catch, throw, and finally.

    To manually throw an exception, use the keyword throw.
    Any code that absolutely must be executed upon exiting from a try block is
    put in a finally block.

    At the core of exception handling are try and catch. These keywords work
    together, and you can't have a catch without a try. Here is the general
    form of the try/catch exception-handling blocks:


try {
    // block of code to monitor for errors
}
catch (ExcepType1 exOb) {
    // handler for ExcepType1
}
catch (ExcepType2 exOb) {
    // handler for ExcepType2
}


    When an exception is thrown, it is caught by its corresponding catch clause,
    which then processes the exception. As the general form shows, more than
    one catch clause can be associated with a try. The type of the exception
    determines which catch is executed.
    When an exception is caught, the optional exception variable will receive
    its value. If no exception is thrown, then a try block ends normally,
    and all of its catch clauses are bypassed.
    Execution resumes with the first statement following the last catch.
*/

// Demonstrate exception handling.

using System;


class ExcDemo1
{
    static void Main()
    {
        int[] nums = new int[4];

        try
        {
            Console.WriteLine("Before exception is generated.");

            // Generate an index out-of-bounds exception.
            for(int i=0; i < 10; i++)
            {
                nums[i] = i;
                Console.WriteLine("nums[{0}]: {1}", i, nums[i]);
            }
            Console.WriteLine("this won't be displayed");
        }
        catch (IndexOutOfRangeException)
        {
            // Catch the exception.
            Console.WriteLine("Index out-of-bounds!");
        }

        Console.WriteLine("After catch block.");
    }
}
