/*
    The Reference Type
    It is useful to restrict the generic type to a reference type.
    Here is the general form of the reference type constraint:

where T : class

    In this form of the where clause, the keyword class specifies that
    T must be a reference type. Thus, an attempt to use a value type,
    such as int or bool, for T will result in a compilation error.
*/


// Demonstrate a reference constraint.
using System;


class MyClass
{
    //...
}


// Use a reference constraint.
class Test<T> where T : class
{
    T obj;
    public Test()
    {
        // The following statement is legal only
        // because T is guaranteed to be a reference
        // type, which can be assigned the value null.
        obj = null;
    }
    // ...
}


class ClassConstraintDemo
{
    static void Main()
    {
        // The following is OK because MyClass is a class.
        Test<MyClass> x = new Test<MyClass>();

        // The next line is in error because int is a value type.
        // Test<int> y = new Test<int>();
    }
}
