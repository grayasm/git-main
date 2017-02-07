// See README.txt for an explanation.
// In short, C# Generics are similar with C++ Templates.

// A simple generic class.

using System;


/* In the following Gen class, T is a type parameter
   that will be replaced by a real type when an object
   of type Gen is created. */

class Gen<T>
{
    T ob; // declare a variable of type T

    // Notice that this constructor has a parameter of type T.
    public Gen(T o)
    {
        ob = o;
    }

    // Return ob, which is of type T.
    public T GetOb()
    {
        return ob;
    }

    // Show type of T.
    public void ShowType()
    {
        Console.WriteLine("Type of T is " + typeof(T));
    }
}


// Demonstrate the generic class.
class GenericsDemo
{
    static void Main()
    {
        // Create a Gen reference for int.
        Gen<int> iOb;

        // Create a Gen<int> object and assign its reference to iOb.
        iOb = new Gen<int>(102);

        // Show the type of data used by iOb.
        iOb.ShowType();

        // Get the value in iOb.
        int v = iOb.GetOb();
        Console.WriteLine("value: " + v);
        Console.WriteLine();

        // Create a Gen object for strings.
        Gen<string> strOb = new Gen<string>("Generics add power.");

        // Show the type of data stored in strOb.
        strOb.ShowType();

        // Get the value in strOb.
        string str = strOb.GetOb();
        Console.WriteLine("value: " + str);
    }
}
