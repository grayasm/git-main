using System;

class Destruct
{
    public int x;

    public Destruct(int i)
    {
        x = i;
    }

    // Called when object is recycled.
    ~Destruct()
    {
        Console.WriteLine("Destructing " + x);
    }

    // Generates an object that is immediately destroyed.
    public void Generator(int i)
    {
        Destruct o = new Destruct(i);
    }
}


class DestructDemo
{
    static void Main()
    {
        int count;
        Destruct ob = new Destruct(0);

        /* Now, generate a large number of objects.
           At some point, garbage collection will occur.
           Note: You might need to increase the number
           of objects generated in order to force
           garbage collection.
        */
        for(count=1; count < 100000; count++)
            ob.Generator(count);

        Console.WriteLine("Done");
    }
}