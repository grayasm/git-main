/*
    Return a Value from an Anonymous Method

    An anonymous method can return a value. The value is returned by use
    of the return statement, which works the same in an anonymous method
    as it does in a named method. As you would expect, the type of the
    return value must be compatible with the return type specified by the
    delegate.
*/


// Demonstrate an anonymous method that returns a value.

using System;


// This delegate returns a value.
delegate int CountIt(int end);

class AnonMethDemo3
{
    static void Main()
    {
        int result;

        // Here, the ending value for the count
        // is passed to the anonymous method.
        // A summation of the count is returned.

        CountIt count = delegate (int end) {

            int sum = 0;
            for(int i=0; i <= end; i++)
            {
                Console.WriteLine(i);
                sum += i;
            }

            return sum; // return a value from an anonymous method
        };

        result = count(3);
        Console.WriteLine("Summation of 3 is " + result);
        Console.WriteLine();

        result = count(5);
        Console.WriteLine("Summation of 5 is " + result);
    }
}
