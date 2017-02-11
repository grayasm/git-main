/*
    Using fixed
    The fixed modifier is often used when working with pointers.
    It prevents a managed variable from being moved by the garbage
    collector. This is needed when a pointer refers to a field in a
    class object, for example. Because the pointer has no knowledge
    of the actions of the garbage collector, if the object is moved,
    the pointer will point to the wrong object.
    Here is the general form of fixed:

fixed (type* p = &fixedObj) {
    // use fixed object
}

*/


// Demonstrate fixed.
using System;


class Test
{
    public int num;

    public Test(int i) { num = i; }
}


class FixedCode
{
    // Mark Main as unsafe.
    unsafe static void Main()
    {
        Test o = new Test(19);

        fixed (int* p = &o.num)   // use fixed to put address of o.num into p
        {
            Console.WriteLine("Initial value of o.num is " + *p);

            *p = 10; // assign 10 to o.num via p

            Console.WriteLine("New value of o.num is " + *p);
        }
    }
}