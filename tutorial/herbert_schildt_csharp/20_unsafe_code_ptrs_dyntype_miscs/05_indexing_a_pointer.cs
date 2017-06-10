/*
    Indexing a Pointer
    When a pointer refers to an array, the pointer can be indexed as if
    it were an array. This syntax provides an alternative to pointer
    arithmetic that can be more convenient in some situations.
    Here is an example:
*/


// Index a pointer as if it were an array.
using System;


class PtrIndexDemo
{
    unsafe static void Main()
    {
        int[] nums = new int[10];

        // Index a pointer.
        Console.WriteLine("Index pointer like array.");
        fixed (int* p = nums)
        {
            for(int i=0; i < 10; i++)
                p[i] = i; // index pointer like array

            for(int i=0; i < 10; i++)
                Console.WriteLine("p[{0}]: {1} ", i, p[i]);
        }


        // Use pointer arithmetic.
        Console.WriteLine("\nUse pointer arithmetic.");
        fixed (int* p = nums)
        {
            for(int i=0; i < 10; i++)
                *(p+i) = i; // use pointer arithmetic

            for(int i=0; i < 10; i++)
                Console.WriteLine("*(p+{0}): {1} ", i, *(p+i));
        }
    }
}
