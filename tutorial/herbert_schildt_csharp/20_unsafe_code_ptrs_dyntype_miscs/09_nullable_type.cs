/*
    Nullable Basics
    A nullable type is a special version of a value type that is
    represented by a structure. In addition to the values defined
    by the underlying type, a nullable type can also store the
    value null. Thus, a nullable type has the same range and
    characteristics as its underlying type. It simply adds the
    ability to represent a value that indicates that a variable
    of that type is unassigned. Nullable types are objects of
    System.Nullable<T>, where T must be a nonnullable value type.
*/


// Demonstrate a nullable type.
using System;


class NullableDemo
{
    static void Main()
    {
        int? count = null;

        if(count.HasValue)
            Console.WriteLine("count has this value: " + count.Value);
        else
            Console.WriteLine("count has no value");

        count = 100;

        if(count.HasValue)
            Console.WriteLine("count has this value: " + count.Value);
        else
            Console.WriteLine("count has no value");
    }
}