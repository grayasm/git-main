/*
    Structures
    As you know, classes are reference types. This means that class objects
    are accessed through a reference. This differs from the value types,
    which are accessed directly. However, sometimes it would be useful to
    be able to access an object directly, in the way that value types are.
    One reason for this is efficiency. Accessing class objects through a
    reference adds overhead onto every access. It also consumes space.
    For very small objects, this extra space might be significant.
    To address these concerns, C# offers the structure.

    A structure is similar to a class, but is a value type, rather than a
    reference type. Structures are declared using the keyword struct and
    are syntactically similar to classes.
    Here is the general form of a struct:

struct name : interfaces {
    // member declarations
}

    Structures cannot inherit other structures or classes or be used as
    a base for other structures or classes. (All structures do, however,
    implicitly inherit System.ValueType, which inherits object.)

    However, a structure can implement one or more interfaces. These are
    specified after the structure name using a comma-separated list.

    Like classes, structure members include methods, fields, indexers,
    properties, operator methods, and events. Structures can also define
    constructors, but not destructors. However, you cannot define a
    default (parameterless) constructor for a structure. The reason for this
    is that a default constructor is automatically defined for all structures,
    and this default constructor can’t be changed. The default constructor
    initializes the fields of a structure to their default value.

    Since structures do not support inheritance, structure members cannot
    be specified as abstract, virtual, or protected.

    A structure object can be created using new in the same way as a class
    object, but it is not required. When new is used, the specified constructor
    is called. When new is not used, the object is still created, but it is
    not initialized. Thus, you will need to perform any initialization manually.
*/


// Demonstrate a structure.

using System;


// Define a structure.
struct Book
{
    public string Author;
    public string Title;
    public int Copyright;

    public Book(string a, string t, int c)
    {
        Author = a;
        Title = t;
        Copyright = c;
    }
}


// Demonstrate Book structure.
class StructDemo
{
    static void Main()
    {
        Book book1 = new Book("Herb Schildt",
                              "C# 4.0: The Complete Reference",
                              2010); // explicit constructor

        Book book2 = new Book(); // default constructor
        Book book3; // no constructor

        Console.WriteLine(book1.Title + " by " + book1.Author +
                          ", (c) " + book1.Copyright);

        Console.WriteLine();

        if(book2.Title == null)
            Console.WriteLine("book2.Title is null.");

        // Now, give book2 some info.
        book2.Title = "Brave New World";
        book2.Author = "Aldous Huxley";
        book2.Copyright = 1932;

        Console.Write("book2 now contains: ");
        Console.WriteLine(book2.Title + " by " + book2.Author +
                          ", (c) " + book2.Copyright);
        Console.WriteLine();

        // Console.WriteLine(book3.Title); // error, must initialize first
        book3.Title = "Red Storm Rising";
        Console.WriteLine(book3.Title); // now OK
    }
}
