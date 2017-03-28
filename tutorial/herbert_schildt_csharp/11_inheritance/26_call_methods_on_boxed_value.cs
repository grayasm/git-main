/*
    Boxing and unboxing allow C#’s type system to be fully unified.
    All types derive from object. A reference to any type can be assigned
    to a variable of type object. Boxing and unboxing automatically handle
    the details for the value types.

    Furthermore, because all types are derived from object, they all have
    access to object’s methods.
*/

// Boxing makes it possible to call methods on a value!

using System;


class MethOnValue
{
    static void Main()
    {
        Console.WriteLine(10.ToString());
    }
}
