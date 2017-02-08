/*
    Generic Interfaces
    In addition to generic classes and methods, you can also have
    generic interfaces. Generic interfaces are specified just like
    generic classes.
*/

// Demonstrate a generic interface.
using System;

public interface ISeries<T>
{
    T GetNext(); // return next element in series
    void Reset(); // restart the series
    void SetStart(T v); // set the starting element
}


// Implement ISeries.
class ByTwos<T> : ISeries<T>
{
    T start;
    T val;

    // This delegate defines the form of a method
    // that will be called when the next element in
    // the series is needed.
    public delegate T IncByTwo(T v);

    // This delegate reference will be assigned the
    // method passed to the ByTwos constructor.
    IncByTwo incr;

    public ByTwos(IncByTwo incrMeth)
    {
        start = default(T);
        val = default(T);
        incr = incrMeth;
    }

    public T GetNext()
    {
        val = incr(val);
        return val;
    }

    public void Reset()
    {
        val = start;
    }

    public void SetStart(T v)
    {
        start = v;
        val = start;
    }
}


class ThreeD
{
    public int x, y, z;
    public ThreeD(int a, int b, int c)
    {
        x = a;
        y = b;
        z = c;
    }
}


class GenIntfDemo
{
    // Define plus two for int.
    static int IntPlusTwo(int v)
    {
        return v + 2;
    }

    // Define plus two for double.
    static double DoublePlusTwo(double v)
    {
        return v + 2.0;
    }

    // Define plus two for ThreeD.
    static ThreeD ThreeDPlusTwo(ThreeD v)
    {
        if(v==null) return new ThreeD(0, 0, 0);
        else return new ThreeD(v.x + 2, v.y + 2, v.z + 2);
    }

    static void Main()
    {
        // Demonstrate int series.
        ByTwos<int> intBT = new ByTwos<int>(IntPlusTwo);
        for(int i=0; i < 5; i++)
            Console.Write(intBT.GetNext() + " ");
        Console.WriteLine();

        // Demonstrate double series.
        ByTwos<double> dblBT = new ByTwos<double>(DoublePlusTwo);
        dblBT.SetStart(11.4);

        for(int i=0; i < 5; i++)
            Console.Write(dblBT.GetNext() + " ");
        Console.WriteLine();

        // Demonstrate ThreeD series.
        ByTwos<ThreeD> ThrDBT = new ByTwos<ThreeD>(ThreeDPlusTwo);
        ThreeD coord;
        for(int i=0; i < 5; i++)
        {
            coord = ThrDBT.GetNext();
            Console.Write(coord.x + "," + coord.y + "," + coord.z + " ");
        }
        Console.WriteLine();
    }
}
