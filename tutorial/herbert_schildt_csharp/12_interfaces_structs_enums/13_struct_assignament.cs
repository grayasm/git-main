/*
    When you assign one structure to another, a copy of the object is made.
    This is an important way in which struct differs from class. As explained
    earlier in this book, when you assign one class reference to another,
    you are simply making the reference on the left side of the assignment
    refer to the same object as that referred to by the reference on the
    right. When you assign one struct variable to another, you are making a
    copy of the object on the right.
*/

// Copy a struct.

using System;


// Define a structure.
struct MyStruct
{
    public int x;
}


// Demonstrate structure assignment.
class StructAssignment
{
    static void Main()
    {
        MyStruct a;
        MyStruct b;

        a.x = 10;
        b.x = 20;

        Console.WriteLine("a.x {0}, b.x {1}", a.x, b.x);

        a = b;
        b.x = 30;
        Console.WriteLine("a.x {0}, b.x {1}", a.x, b.x);
    }
}
