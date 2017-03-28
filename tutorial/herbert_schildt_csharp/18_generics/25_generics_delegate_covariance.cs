/*
    Variant Delegates
    As explained in Chapter 15, non-generic delegates already support
    covariance and contravariance as they relate to method return types
    and parameter types. Beginning with C# 4.0, these features are
    expanded for generic delegates to include type parameter covariance
    and contravariance.

// Declare a generic delegate that is contravariant on T.
delegate bool SomeOp<in T>(T obj);

// Declare a generic delegate that is covariant on T.
delegate T AnotherOp<out T, V>(V obj);

*/

// Demonstrate covariance and contravariance with a generic delegate.
using System;


// Declare a generic delegate that is contravariant on T.
delegate bool SomeOp<in T>(T obj);

// Declare a generic delegate that is covariant on T.
delegate T AnotherOp<out T, V>(V obj);


class Alpha
{
    public int Val { get; set; }
    public Alpha(int v) { Val = v; }
}

class Beta : Alpha
{
    public Beta(int v) : base(v) { }
}

class GenDelegateVarianceDemo
{
    // Return true if obj.Val is even.
    static bool IsEven(Alpha obj)
    {
        if((obj.Val % 2) == 0) return true;
        return false;
    }

    static Beta ChangeIt(Alpha obj)
    {
        return new Beta(obj.Val +2);
    }

    static void Main()
    {
        Alpha objA = new Alpha(4);
        Beta objB = new Beta(9);

        // First demonstrate contravariance.
        // Declare a SomeOp<Alpha> delegate and set it to IsEven.
        SomeOp<Alpha> checkIt = IsEven;

        // Declare a SomeOp<Beta> delegate.
        SomeOp<Beta> checkIt2;

        // Now, assign the SomeOp<Alpha> delegate the SomeOp<Beta> delegate.
        // *** This is legal only because of contravariance. ***
        checkIt2 = checkIt;


        // Call through the delegate.
        Console.WriteLine(checkIt2(objB));

        // Now, demonstrate covariance.
        // First, declare two AnotherOp delegates.
        // Here, the return type is Beta and the parameter type is Alpha.
        // Notice that modifyIt is set to ChangeIt.
        AnotherOp<Beta, Alpha> modifyIt = ChangeIt;

        // Here, the return type is Alpha and the parameter type is Alpha.
        AnotherOp<Alpha, Alpha> modifyIt2;

        // Now, assign modifyIt to modifyIt2.
        // *** This statement is legal only because of covariance. ***
        modifyIt2 = modifyIt;

        // Actually call the method and display the results.
        objA = modifyIt2(objA);
        Console.WriteLine(objA.Val);
    }
}
