/*
    The object Class

    C# defines one special class called object that is an implicit base class
    of all other classes and for all other types (including the value types).
    In other words, all other types are derived from object. This means that
    a reference variable of type object can refer to an object of any other
    type. Also, since arrays are implemented as objects, a variable of type
    object can also refer to any array.
    Technically, the C# name object is just another name for System.Object,
    which is part of the .NET Framework class library.

    The object class defines the methods shown in Table 11-1, which means
    that they are available in every object:

public virtual bool Equals(object obj)
public static bool Equals(object objA, object objB)
protected virtual Finalize( )
public virtual int GetHashCode( )
public Type GetType( )
protected object MemberwiseClone( )
public static bool ReferenceEquals(object objA, object objB)
public virtual string ToString( )
*/


// Demonstrate ToString()

using System;


class MyClass
{
    static int count = 0;
    int id;

    public MyClass()
    {
        id = count;
        count++;
    }

    public override string ToString()
    {
        return "MyClass object #" + id;
    }
}


class Test
{
    static void Main()
    {
        MyClass ob1 = new MyClass();
        MyClass ob2 = new MyClass();
        MyClass ob3 = new MyClass();

        Console.WriteLine(ob1);
        Console.WriteLine(ob2);
        Console.WriteLine(ob3);
    }
}
