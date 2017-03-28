/*
    A Closer Look at the Exception Class
    Exception defines several properties. Three of the most interesting are
    Message, StackTrace, and TargetSite. All are read-only.

    Message contains a string that describes the nature of the error.
    StackTrace contains a string that contains the stack of calls that lead to
    the exception.
    TargetSite obtains an object that specifies the method that generated the
    exception.

    Exception also defines several methods. One that you will often use is
    ToString( ), which returns a string that describes the exception.
    ToString( ) is automatically called when an exception is displayed via
    WriteLine( ), for example.
*/

using System;

class ExcTest
{
    public static void GenException()
    {
        int[] nums = new int[4];
        Console.WriteLine("Before exception is generated.");

        // Generate an index out-of-bounds exception.
        for(int i=0; i < 10; i++)
        {
            nums[i] = i;
            Console.WriteLine("nums[{0}]: {1}", i, nums[i]);
        }

        Console.WriteLine("this won't be displayed");
    }
}

class UseExcept
{
    static void Main()
    {
        try {
            ExcTest.GenException();
        }
        catch (IndexOutOfRangeException exc)
        {
            Console.WriteLine("Standard message is: ");
            Console.WriteLine(exc); // calls ToString()
            Console.WriteLine("Stack trace: " + exc.StackTrace);
            Console.WriteLine("Message: " + exc.Message);
            Console.WriteLine("TargetSite: " + exc.TargetSite);
        }

        Console.WriteLine("After catch block.");
    }
}
