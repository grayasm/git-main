/*
    Using the new( ) Constructor Constraint
    The new( ) constructor constraint enables you to instantiate an object
    of a generic type. Normally, you cannot create an instance of a generic
    type parameter. However, the new( ) constraint changes this because it
    requires that a type argument supply a public parameterless constructor.

    This can be the default constructor provided automatically when no
    explicit constructor is declared or a parameterless constructor
    explicitly defined by you. With the new( ) constraint in place, you
    can invoke the parameterless constructor to create an object.
*/

// Demonstrate a new() constructor constraint.

using System;


class MyClass
{
    public MyClass()
    {
        // ...
    }
    //...
}


class Test<T> where T : new()
{
    T obj;
    public Test()
    {
        // This works because of the new() constraint.
        obj = new T(); // create a T object
    }
    // ...
}


class ConsConstraintDemo
{
    static void Main()
    {
        Test<MyClass> x = new Test<MyClass>();
    }
}
