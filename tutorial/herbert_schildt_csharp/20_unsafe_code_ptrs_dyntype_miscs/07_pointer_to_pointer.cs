using System;


class MultipleIndirect
{
    unsafe static void Main()
    {
        int x; // holds an int value

        int* p; // holds an int pointer

        int** q; // holds a pointer to an int pointer

        x = 10;

        p = &x; // put address of x into p

        q = &p; // put address of p into q

        Console.WriteLine(**q); // display the value of x
    }
}
