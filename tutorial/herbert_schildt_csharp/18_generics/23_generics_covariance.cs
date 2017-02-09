/*
    Using Covariance in a Generic Interface
    As it applies to a generic interface, covariance is the feature
    that enables a method to return a type that is derived from the
    class specified by a type parameter. In the past, because of
    the strict type-checking applied to generics, the return type had
    to match the type parameter precisely. Covariance relaxes this
    rule in a type-safe way. A covariant type parameter is declared by
    preceding its name with the keyword out.

// This generic interface supports covariance.
public interface IMyCoVarGenIF<out T> {
       T GetObject();
}

*/


// Demonstrate generic interface covariance.
using System;


// This generic interface supports covariance.
public interface IMyCoVarGenIF<out T>
{
    T GetObject();
}


// Implement the IMyCoVarGenIF interface.
class MyClass<T> : IMyCoVarGenIF<T>
{
    T obj;
    public MyClass(T v) { obj = v; }

    public T GetObject() { return obj; }
}


// Create a simple class hierarchy.
class Alpha
{
    string name;
    public Alpha(string n) { name = n; }
    public string GetName() { return name; }
    // ...
}


class Beta : Alpha
{
    public Beta(string n) : base(n) { }
    // ...
}


class VarianceDemo
{
    static void Main()
    {
        // Create a IMyCoVarGenIF reference to a MyClass<Alpha> object.
        // This is legal with or without covariance.
        IMyCoVarGenIF<Alpha> AlphaRef =
            new MyClass<Alpha>(new Alpha("Alpha #1"));

        Console.WriteLine("Name of object referred to by AlphaRef is " +
        AlphaRef.GetObject().GetName());

        // Now create a MyClass<Beta> object and assign it to AlphaRef.
        // *** This line is legal because of covariance. ***
        AlphaRef = new MyClass<Beta>(new Beta("Beta #1"));
        Console.WriteLine("Name of object referred to by AlphaRef is now " +
        AlphaRef.GetObject().GetName());
    }
}
