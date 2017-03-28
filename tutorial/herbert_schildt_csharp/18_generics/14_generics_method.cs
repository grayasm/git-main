/*
    Creating a Generic Method

    Methods inside a generic class can make use of a class’ type parameter
    and are, therefore, automatically generic relative to the type parameter.
    However, it is possible to declare a generic method that uses one or
    more type parameters of its own. Furthermore, it is possible to create
    a generic method that is enclosed within a non-generic class.
*/

// Demonstrate a generic method.
using System;


// A class of array utilities. Notice that this is not
// a generic class.
class ArrayUtils
{
    // Copy an array, inserting a new element
    // in the process. This is a generic method.
    public static bool CopyInsert<T>(T e, uint idx,
                                     T[] src, T[] target)
    {
        // See if target array is big enough.
        if(target.Length < src.Length+1)
            return false;

        // Copy src to target, inserting e at idx in the process.
        for(int i=0, j=0; i < src.Length; i++, j++)
        {
            if(i == idx)
            {
                target[j] = e;
                j++;
            }
            target[j] = src[i];
        }
        return true;
    }
}


class GenMethDemo
{
    static void Main()
    {
        int[] nums = { 1, 2, 3 };
        int[] nums2 = new int[4];

        // Display contents of nums.
        Console.Write("Contents of nums: ");
        foreach(int x in nums)
            Console.Write(x + " ");
        Console.WriteLine();

        // Operate on an int array.
        ArrayUtils.CopyInsert(99, 2, nums, nums2);

        // Display contents of nums2.
        Console.Write("Contents of nums2: ");
        foreach(int x in nums2)
            Console.Write(x + " ");
        Console.WriteLine();

        // Now, use copyInsert on an array of strings.
        string[] strs = { "Generics", "are", "powerful."};
        string[] strs2 = new string[4];

        // Display contents of strs.
        Console.Write("Contents of strs: ");
        foreach(string s in strs)
            Console.Write(s + " ");
        Console.WriteLine();

        // Insert into a string array.
        ArrayUtils.CopyInsert("in C#", 1, strs, strs2);

        // Display contents of strs2.
        Console.Write("Contents of strs2: ");
        foreach(string s in strs2)
            Console.Write(s + " ");

        Console.WriteLine();
        // This call is invalid because the first argument
        // is of type double, and the third and fourth arguments
        // have element types of int.
        // ArrayUtils.CopyInsert(0.01, 2, nums, nums2);
    }
}
