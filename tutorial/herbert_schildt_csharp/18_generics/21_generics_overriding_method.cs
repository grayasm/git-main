/*
    Overriding Virtual Methods in a Generic Class
    A virtual method in a generic class can be overridden just like
    any other method. For example, consider this program in which the
    virtual method GetOb( ) is overridden:
*/

// Overriding a virtual method in a generic class.
using System;


// A generic base class.
class Gen<T>
{
    protected T ob;
    public Gen(T o)
    {
        ob = o;
    }

    // Return ob. This method is virtual.
    public virtual T GetOb()
    {
        Console.Write("Gen’s GetOb(): ");
        return ob;
    }
}


// A derived class of Gen that overrides GetOb().
class Gen2<T> : Gen<T>
{
    public Gen2(T o) : base(o) { }

    // Override GetOb().
    public override T GetOb()
    {
        Console.Write("Gen2’s GetOb(): ");
        return ob;
    }
}


// Demonstrate generic method override.
class OverrideDemo
{
    static void Main()
    {
        // Create a Gen object for int.
        Gen<int> iOb = new Gen<int>(88);

        // This calls Gen’s version of GetOb().
        Console.WriteLine(iOb.GetOb());

        // Now, create a Gen2 object and assign its
        // reference to iOb (which is a Gen<int> variable).
        iOb = new Gen2<int>(99);

        // This calls Gen2’s version of GetOb().
        Console.WriteLine(iOb.GetOb());
    }
}
