/*
    Anonymous Methods

    An anonymous method is one way to create an UNNAMED block of code that is
    associated with a specific delegate instance. An anonymous method is
    created by following the keyword delegate with a block of code.
*/

// Demonstrate an anonymous method.

using System;


// Declare a delegate type.
delegate void CountIt();

class AnonMethDemo
{
    static void Main()
    {
        // Here, the code for counting is passed
        // as an anonymous method.

        CountIt count = delegate {

            // This is the block of code passed to the delegate.
            for(int i=0; i <= 5; i++)
                Console.WriteLine(i);

        }; // notice the semicolon

        count();
    }
}