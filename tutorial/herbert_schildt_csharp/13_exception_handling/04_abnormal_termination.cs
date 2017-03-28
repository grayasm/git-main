/*
    The exception won’t be caught. For example, the following program tries
    to catch an array boundary error with a catch for a DivideByZeroException
    (another built-in exception). When the array boundary is overrun, an
    IndexOutOfRangeException is generated, but it won’t be caught by the catch.
    This results in abnormal program termination.
*/

// This won't work!

using System;


class ExcTypeMismatch
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
        /* Can't catch an array boundary error with a
           DivideByZeroException. */
        catch (DivideByZeroException)
        {
            // Catch the exception.
            Console.WriteLine("Index out-of-bounds!");
        }

        Console.WriteLine("After catch block.");
    }
}
