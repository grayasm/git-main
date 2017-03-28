/*
    stackalloc
    You can allocate memory from the stack by using stackalloc.
    It can be used only when initializing local variables and has
    this general form:

type* p = stackalloc type[size]

*/

// Demonstrate stackalloc.
using System;


class UseStackAlloc
{
    unsafe static void Main()
    {
        int* ptrs = stackalloc int[3];

        ptrs[0] = 1;
        ptrs[1] = 2;
        ptrs[2] = 3;

        for(int i=0; i < 3; i++)
            Console.WriteLine(ptrs[i]);
    }
}
