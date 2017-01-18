/*
    Boxing and Unboxing
    As explained, all C# types, including the value types, are derived from
    object. Thus, a reference of type object can be used to refer to any
    other type, including value types.

    When an object reference refers to a value type, a process known as
    boxing occurs. Boxing causes the value of a value type to be stored
    in an object instance. Thus, a value type is "boxed" inside an object.
    This object can then be used like any other object. In all cases,
    boxing occurs automatically. You simply assign a value to an object
    reference. C# handles the rest.

    Unboxing is the process of retrieving a value from a boxed object.
    This action is performed using an explicit cast from the object
    reference to its corresponding value type.

    Attempting to unbox an object into a different type will result
    in a runtime error.
*/


// A simple boxing/unboxing example.

using System;


class BoxingDemo
{
    static void Main()
    {
        int x;

        object obj;
        x = 10;

        obj = x;             // box x into an object
        int y = (int)obj;    // unbox obj into an int

        Console.WriteLine(y);
    }
}
