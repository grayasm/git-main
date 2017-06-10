/*
    Interface Properties
    Like methods, properties are specified in an interface without any body.
    Here is the general form of a property specification:

// interface property
type name {
    get;
    set;
}

    Although the declaration of a property in an interface looks similar
    to how an autoimplemented property is declared in a class, the two are
    not the same. The interface declaration does not cause the property
    to be auto-implemented. It only specifies the name and type of the
    property. Implementation is left to each implementing class.
    Also, no access modifiers are allowed on the accessors when a property
    is declared in an interface. Thus, the set accessor, for example,
    cannot be specified as private in an interface.
*/


// Use a property in an interface.

using System;


public interface ISeries
{
    // An interface property.
    int Next
    {
        get; // return the next number in series
        set; // set next number
    }
}


// Implement ISeries.
class ByTwos : ISeries
{
    int val;

    public ByTwos()
    {
        val = 0;
    }

    // Get or set value.
    public int Next
    {
        get {
            val += 2;
            return val;
        }

        set {
            val = value;
        }
    }
}


// Demonstrate an interface property.
class SeriesDemo3
{
    static void Main()
    {
        ByTwos ob = new ByTwos();

        // Access series through a property.
        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob.Next);

        Console.WriteLine("\nStarting at 21");
        ob.Next = 21;

        for(int i=0; i < 5; i++)
            Console.WriteLine("Next value is " + ob.Next);
    }
}
