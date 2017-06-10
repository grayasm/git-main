/*
    Runtime Type Identification
    C# includes three keywords that support runtime type identification:
    is, as, and typeof.
*/

/*
    Using typeof
    Although useful in their own ways, the as and is operators simply
    test the compatibility of two types. Often, you will need to obtain
    information about a type. To do this, C# supplies the typeof operator.

    It retrieves a System.Type object for a given type. Using this object,
    you can determine the type’s characteristics.
    The typeof operator has this general form:

typeof(type)

*/

// Demonstrate typeof.

using System;
using System.IO;


class UseTypeof
{
    static void Main()
    {
        Type t = typeof(StreamReader);

        Console.WriteLine(t.FullName);

        if(t.IsClass)
            Console.WriteLine("Is a class.");

        if(t.IsAbstract)
            Console.WriteLine("Is abstract.");
        else
            Console.WriteLine("Is concrete.");
    }
}
