/*
    The internal Access Modifier

    In addition to the access modifiers public, private, and protected,
    which you have been using throughout this book, C# also defines internal.

    The internal modifier declares that a member is known throughout all files
    in an assembly, but unknown outside that assembly.

    Thus, in simplified terms, a member marked as internal is known throughout
    a program, but not elsewhere. The internal access modifier is particularly
    useful when creating software components.

    The internal modifier can be applied to classes and members of classes
    and to structures and members of structures. The internal modifier can
    also be applied to interface and enumeration declarations.
    You can use protected in conjunction with internal to produce the protected
    internal access modifier pair. The protected internal access level can be
    given only to class members. A member declared with protected internal
    access is accessible within its own assembly or to derived types.
*/

// Use internal.

using System;

class InternalTest
{
    internal int x;
}

class InternalDemo
{
    static void Main()
    {
        InternalTest ob = new InternalTest();

        ob.x = 10; // can access -- in same file

        Console.WriteLine("Here is ob.x: " + ob.x);
    }
}
