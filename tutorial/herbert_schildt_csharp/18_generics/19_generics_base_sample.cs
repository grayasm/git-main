// A derived class can add its own type parameters.
using System;

// A generic base class.
class Gen<T>
{
    T ob; // declare a variable of type T

    // Pass the constructor a reference of type T.
    public Gen(T o)
    {
        ob = o;
    }

    // Return ob.
    public T GetOb()
    {
        return ob;
    }
}


// A derived class of Gen that defines a second
// type parameter, called V.
class Gen2<T, V> : Gen<T>
{
    V ob2;

    public Gen2(T o, V o2) : base(o)
    {
        ob2 = o2;
    }

    public V GetObj2()
    {
        return ob2;
    }
}


// Create an object of type Gen2.
class GenHierDemo2
{
    static void Main()
    {
        // Create a Gen2 object for string and int.
        Gen2<string, int> x = new Gen2<string, int>("Value is: ", 99);
        Console.Write(x.GetOb());
        Console.WriteLine(x.GetObj2());
    }
}
