/*
    Creating a Default Value of a Type Parameter
    For this generic:

class Test<T> {
     T obj;

    initialization with default value like these:
    obj = null;  // or
    obj = 0;

    does not work in all cases. Solution is:
    obj = default(type);
*/


// Demonstrate the default operator.
using System;


class MyClass
{
    //...
}

// Construct a default value of T.
class Test<T>
{
    public T obj;
    public Test()
    {
        // The following statement would work only for reference types.
        // obj = null; // can’t use
        // The following statement will work only for numeric value types.
        // obj = 0; // can’t use
        // This statement works for both reference and value types.

        obj = default(T); // Works!
    }
    // ...
}


class DefaultDemo
{
    static void Main()
    {
        // Construct Test using a reference type.
        Test<MyClass> x = new Test<MyClass>();
        if(x.obj == null)
            Console.WriteLine("x.obj is null.");

        // Construct Test using a value type.
        Test<int> y = new Test<int>();
        if(y.obj == 0)
            Console.WriteLine("y.obj is 0.");
    }
}
