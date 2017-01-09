using System;

class Example
{
    static void Main()
    {
        /*
            This program attempts to declare a variable
            in an inner scope with the same name as one
            defined in an outer scope.
            *** This program will not compile. ***
        */
        int count;
        for(count = 0; count < 10; count = count+1)
        {
           Console.WriteLine("This is count: " + count);

           // int count; // illegal!!!
           for(count = 0; count < 2; count++)
                     Console.WriteLine("This program is in error!");
        }
    }
}