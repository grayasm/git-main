// A simple demonstration that uses object initializers.

using System;


class MyClass
{
    public int Count;
    public string Str;
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
