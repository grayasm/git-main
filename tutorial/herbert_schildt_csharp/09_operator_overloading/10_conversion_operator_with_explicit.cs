/*
    Conversion Operators
    In some situations, you will want to use an object of a class in an
    expression involving other types of data. Sometimes, overloading one or
    more operators can provide the means of doing this. However, in other
    cases, what you want is a simple type conversion from the class type to the
    target type. To handle these cases, C# allows you to create a special type
    of operator method called a conversion operator.

    A conversion operator converts an object of your class into another type.
    Conversion operators help fully integrate class types into the C#
    programming environment by allowing objects of a class to be freely mixed
    with other data types as long as a conversion to those other types is
    defined.

    There are two forms of conversion operators, implicit and explicit.
    The general form for each is shown here:

public static operator implicit target-type(source-type v) { return value; }
public static operator explicit target-type(source-type v) { return value; }

       Here, target-type is the target type that you are converting to;
       source-type is the type you are converting from; and value is the value
       of the class after conversion. The conversion operators return data of
       type target-type, and no other return type specifier is allowed.
       If the conversion operator specifies implicit, then the conversion is
       invoked automatically, such as when an object is used in an expression
       with the target type. When the conversion operator specifies explicit,
       the conversion is invoked when a cast is used. You cannot define both an
       implicit and explicit conversion operator for the same target and source
       types.
*/

// Use an explicit conversion.

using System;


// A three-dimensional coordinate class.
class ThreeD
{
    int x, y, z; // 3-D coordinates
    public ThreeD() { x = y = z = 0; }
    public ThreeD(int i, int j, int k) { x = i; y = j; z = k; }

    // Overload binary +.
    public static ThreeD operator +(ThreeD op1, ThreeD op2)
    {
        ThreeD result = new ThreeD();
        result.x = op1.x + op2.x;
        result.y = op1.y + op2.y;
        result.z = op1.z + op2.z;
        return result;
    }

    // This is now explicit.
    public static explicit operator int(ThreeD op1)
    {
        return op1.x * op1.y * op1.z;
    }

    // Show X, Y, Z coordinates.
    public void Show()
    {
        Console.WriteLine(x + ", " + y + ", " + z);
    }
}

class ThreeDDemo
{
    static void Main()
    {
        ThreeD a = new ThreeD(1, 2, 3);
        ThreeD b = new ThreeD(10, 10, 10);
        ThreeD c = new ThreeD();

        int i;
        Console.Write("Here is a: ");
        a.Show();
        Console.WriteLine();
        Console.Write("Here is b: ");
        b.Show();
        Console.WriteLine();

        c = a + b; // add a and b together
        Console.Write("Result of a + b: ");
        c.Show();
        Console.WriteLine();

        i = (int) a; // explicitly convert to int -- cast required
        Console.WriteLine("Result of i = a: " + i);
        Console.WriteLine();

        i = (int)a * 2 - (int)b; // casts required
        Console.WriteLine("result of a * 2 - b: " + i);
    }
}
