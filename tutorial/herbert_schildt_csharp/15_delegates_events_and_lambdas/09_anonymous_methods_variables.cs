/*
    Use Outer Variables with Anonymous Methods

    A local variable or parameter whose scope includes an anonymous method
    is called an OUTER VARIABLE.

    An anonymous method has access to and can use these outer variables.
    When an outer variable is used by an anonymous method, that variable
    is said to be captured. A captured variable will stay in existence at
    least until the delegate that captured it is subject to garbage collection.
    Thus, even though a local variable will normally cease to exist when its
    block is exited, if that local variable is being used by an anonymous
    method, then that variable will stay in existence at least until the
    delegate referring to that method is destroyed.

    The capturing of a local variable can lead to unexpected results.
*/


// Demonstrate a captured variable.

using System;


// This delegate returns int and takes an int argument.
delegate int CountIt(int end);

class VarCapture
{
    static CountIt Counter()
    {
        int sum = 0;

        // Here, a summation of the count is stored
        // in the captured variable sum.
        CountIt ctObj = delegate (int end) {

            for(int i=0; i <= end; i++)
            {
                Console.WriteLine(i);
                sum += i;
            }

            return sum;
        };

        return ctObj;
    }


    static void Main()
    {
        // Get a counter.
        CountIt count = Counter();
        int result;
        result = count(3);

        Console.WriteLine("Summation of 3 is " + result);
        Console.WriteLine();

        result = count(5);
        Console.WriteLine("Summation of 5 is " + result);
    }
}
