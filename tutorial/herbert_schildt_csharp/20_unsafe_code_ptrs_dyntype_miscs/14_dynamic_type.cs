/*
    Create a Dynamic Type with dynamic.
    With an important exception, the dynamic type is similar to object
    because it can be used to refer to any type of object. The difference
    between object and dynamic is that all type checking related to a
    dynamic type is deferred until runtime. (With object, type checking
    still occurs at compile time.) The benefit of waiting until runtime
    is that, at compile time, a dynamic object is assumed to support any
    operation, including the use of operators, calls to methods, access
    to fields, and so on. This enables code to be compiled without error.
    Of course, if at runtime the object’s actual type does not support
    the operation, then a runtime exception will occur.
*/

// Demonstrate the use of dynamic.
using System;
using System.Globalization;


class DynDemo
{
    static void Main()
    {
        // Declare two dynamic variables.
        dynamic str;
        dynamic val;

        // Implicit conversion to dynamic types is supported.
        // Therefore the following assignments are legal.
        str = "This is a string";
        val = 10;
        Console.WriteLine("str contains " + str);
        Console.WriteLine("val contains " + val + '\n');

        str = str.ToUpper(CultureInfo.CurrentCulture);
        Console.WriteLine("str now contains " + str);

        val = val + 2;
        Console.WriteLine("val now contains " + val + '\n');

        string str2 = str.ToLower(CultureInfo.CurrentCulture);
        Console.WriteLine("str2 contains " + str2);

        // Implicit conversions from dynamic types are supported.
        int x = val * 2;
        Console.WriteLine("x contains " + x);
    }
}
