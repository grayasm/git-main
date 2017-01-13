/*
    Auto-Implemented Properties
    Beginning with C# 3.0, it became possible to implement very simple
    properties without having to explicitly define the variable managed by the
    property. Instead, you can let the compiler automatically supply the
    underlying variable. This is called an auto-implemented property.
    It has the following general form:

type name { get; set; }

    Here, type specifies the type of the property and name specifies the name.
    Notice that get and set are immediately followed by a semicolon. The
    accessors for an auto-implemented property have no bodies. This syntax tells
    the compiler to automatically create a storage location (sometimes referred
    to as a backing field) that holds the value. This variable is not named and
    is not directly available to you. Instead, it can be accessed only through
    the property.

    Here is how a property called UserCount is declared using an
    auto-implemented property:

public int UserCount { get; set; }

    Notice that no variable is explicitly declared. As explained, the compiler
    automatically generates an anonymous field that holds the value. Otherwise,
    UserCount acts like and is used like any other property.

    Unlike normal properties, an auto-implemented property cannot be read-only
    or writeonly. Both the get and set must be specified in all cases.
    However, you can approximate the same effect by declaring either get or set
    as private, as explained in "Use Access Modifiers with Accessors" later in
    this chapter.
    Although auto-implemented properties offer convenience, their use is limited
    to those cases in which you do not need control over the getting or setting
    of the backing field. Remember, you cannot access the backing field
    directly. This means that there is no way to constrain the value an
    auto-implemented property can have. Thus, auto-implemented properties simply
    let the name of the property act as a proxy for the field, itself. However,
    sometimes this is exactly what you want. Also, they can be very useful in
    cases in which properties are used to expose functionality to a third party,
    possibly through a design tool.
*/


// Use object initializers with properties.
using System;


class MyClass
{
    // These are now properties.
    public int Count { get; set; }
    public string Str { get; set; }
}


class ObjInitDemo
{
    static void Main()
    {
        // Construct a MyClass object by using object initializers.
        MyClass obj = new MyClass { Count = 100, Str = "Testing" };
        Console.WriteLine(obj.Count + " " + obj.Str);
    }
}
