/*
    Using Contravariance in a Generic Interface
    As it applies to a generic interface, contravariance is the feature
    that lets a method use an argument whose type is a base class of the
    type specified by the type parameter for that parameter. In the past,
    because of the strict type-checking applied to generics, a method's
    argument type had to match the type parameter precisely. Contravariance
    relaxes this rule in a type-safe way. A contravariant type parameter
    is declared by preceding the type parameter with the keyword in.

// This generic interface supports contravariance.
public interface IMyContraVarGenIF<in T> {
       void Show(T obj);
}

*/


// Demonstrate generic interface contravariance.
using System;


// This generic interface supports contravariance.
public interface IMyContraVarGenIF<in T>
{
    void Show(T obj);
}


// Implement the IMyContraVarGenIF interface.
class MyClass<T> : IMyContraVarGenIF<T>
{
    public void Show(T x) { Console.WriteLine(x); }
}


// Create a simple class hierarchy.
class Alpha
{
    public override string ToString()
    {
        return "This is an Alpha object.";
    }
    // ...
}


class Beta : Alpha
{
    public override string ToString()
    {
        return "This is a Beta object.";
    }
    // ...
}


class VarianceDemo
{
    static void Main()
    {
        // Create an IMyContraVarGenIF<Alpha> reference to a
        // MyClass<Alpha> object.
        // This is legal with or without contravariance.
        IMyContraVarGenIF<Alpha> AlphaRef = new MyClass<Alpha>();

        // Create an IMyContraVarGenIF<beta> reference to a
        // MyClass<Beta> object.
        // This is legal with or without contravariance.
        IMyContraVarGenIF<Beta> BetaRef = new MyClass<Beta>();

        // Create an IMyContraVarGenIF<beta> reference to
        // a MyClass<Alpha> object.
        // *** This is legal because of contravariance. ***
        IMyContraVarGenIF<Beta> BetaRef2 = new MyClass<Alpha>();

        // This call is legal with or without contravariance.
        BetaRef.Show(new Beta());

        // Assign AlphaRef to BetaRef.
        // *** This is legal because of contravariance. ***
        BetaRef = AlphaRef;
        BetaRef.Show(new Beta());
    }
}
