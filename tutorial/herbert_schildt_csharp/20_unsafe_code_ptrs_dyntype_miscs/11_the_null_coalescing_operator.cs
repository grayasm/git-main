/*
    The ?? Operator
    If you attempt to use a cast to convert a nullable object to
    its underlying type, a System.InvalidOperationException will
    be thrown if the nullable object contains a null value.
    This can occur, for example, when you use a cast to assign the
    value of a nullable object to a variable of its underlying type.
    You can avoid the possibility of this exception being thrown by
    using the ?? operator, which is called the null coalescing operator.
    It lets you specify a default value that will be used when the
    nullable object contains null. It also eliminates the need for the cast.
    The ?? operator has this general form:

nullable-object ?? default-value

*/

// Using ??
using System;


class NullableDemo2
{
    // Return a zero balance.
    static double GetZeroBal()
    {
        Console.WriteLine("In GetZeroBal().");
        return 0.0;
    }


    static void Main()
    {
        double? balance = 123.75;
        double currentBalance;

        // Here, GetZeroBal( ) is not called because balance
        // contains a value.

        currentBalance = balance ?? GetZeroBal();

        Console.WriteLine(currentBalance);
    }
}
