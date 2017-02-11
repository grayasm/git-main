// Demonstrate pointers and unsafe.
using System;


class UnsafeCode
{
    // Mark Main as unsafe.
    unsafe static void Main()
    {
        int count = 99;
        int* p;     // create an int pointer
        p = &count; // put address of count into p

        Console.WriteLine("Initial value of count is " + *p);
        *p = 10; // assign 10 to count via p
        Console.WriteLine("New value of count is " + *p);
    }
}
