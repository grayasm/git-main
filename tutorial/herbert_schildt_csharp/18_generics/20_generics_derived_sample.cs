// A non-generic class can be the base class of a generic derived class.
using System;

// A non-generic class.
class NonGen
{
    int num;
    public NonGen(int i)
    {
        num = i;
    }

    public int GetNum()
    {
        return num;
    }
}


// A generic derived class.
class Gen<T> : NonGen
{
    T ob;
    public Gen(T o, int i) : base (i)
    {
        ob = o;
    }

    // Return ob.
    public T GetOb()
    {
        return ob;
    }
}


// Create a Gen object.
class HierDemo3
{
    static void Main()
    {
        // Create a Gen object for string.
        Gen<String> w = new Gen<String>("Hello", 47);
        Console.Write(w.GetOb() + " ");
        Console.WriteLine(w.GetNum());
    }
}
