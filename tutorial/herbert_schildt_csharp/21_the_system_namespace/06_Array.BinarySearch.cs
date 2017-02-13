// Sort and search an array of objects.
using System;


class MyClass : IComparable<MyClass>
{
    public int i;
    public MyClass(int x) { i = x; }

    // Implement IComparable<MyClass>.
    public int CompareTo(MyClass v)
    {
        return i - v.i;
    }
}


class SortDemo
{
    static void Main()
    {
        MyClass[] nums = new MyClass[5];

        nums[0] = new MyClass(5);
        nums[1] = new MyClass(2);
        nums[2] = new MyClass(3);
        nums[3] = new MyClass(4);
        nums[4] = new MyClass(1);

        // Display original order.
        Console.Write("Original order: ");
        foreach(MyClass o in nums)
            Console.Write(o.i + " ");
        Console.WriteLine();


        // Sort the array.
        Array.Sort(nums);

        // Display sorted order.
        Console.Write("Sorted order: ");
        foreach(MyClass o in nums)
            Console.Write(o.i + " ");
        Console.WriteLine();

        // Search for MyClass(2).
        MyClass x = new MyClass(2);
        int idx = Array.BinarySearch(nums, x);
        Console.WriteLine("Index of MyClass(2) is " + idx);
    }
}
