/*
     After the (struct) assignment
     a = b;
     the structure variables a and b are still separate and distinct.
     That is, a does not refer to or relate to b in any way other than
     containing a copy of b’s value. This would not be the case if a and b
     were class references. For example, here is the class version of the
     preceding program:
*/

// Use a class.

using System;


// Now a class.
class MyClass
{
    public int x;
}


// Now show a class object assignment.
class ClassAssignment
{
    static void Main()
    {
        MyClass a = new MyClass();
        MyClass b = new MyClass();

        a.x = 10;
        b.x = 20;

        Console.WriteLine("a.x {0}, b.x {1}", a.x, b.x);
        a = b;
        b.x = 30;
        Console.WriteLine("a.x {0}, b.x {1}", a.x, b.x);
    }
}
