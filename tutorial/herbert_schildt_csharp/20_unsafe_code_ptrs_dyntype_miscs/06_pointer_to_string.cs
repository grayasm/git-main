/*
    Pointers and Strings
    Although strings are implemented as objects in C#, it is possible
    to access the characters in a string through a pointer. To do so,
    you will assign a pointer to the start of the string to a char*
    pointer using a fixed statement like this:

fixed(char* p = str) { // ...

*/


// Use fixed to get a pointer to the start of a string.
using System;


class FixedString
{
    unsafe static void Main()
    {
        string str = "this is a test";

        // Point p to start of str.
        fixed(char* p = str)
        {
            // Display the contents of str via p.
            for(int i=0; p[i] != 0; i++)
                Console.Write(p[i]);
        }

        Console.WriteLine();
    }
}
