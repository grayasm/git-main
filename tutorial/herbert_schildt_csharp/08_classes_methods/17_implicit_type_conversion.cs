// Implicit type conversions can affect overloaded method resolution.

using System;


class Overload2
{
    public void MyMeth(int x)
    {
        Console.WriteLine("Inside MyMeth(int): " + x);
    }

    public void MyMeth(double x)
    {
        Console.WriteLine("Inside MyMeth(double): " + x);
    }
}


class TypeConv
{
    static void Main()
    {
        Overload2 ob = new Overload2();
        int i = 10;
        double d = 10.1;
        byte b = 99;
        short s = 10;
        float f = 11.5F;

        ob.MyMeth(i); // calls ob.MyMeth(int)
        ob.MyMeth(d); // calls ob.MyMeth(double)
        ob.MyMeth(b); // calls ob.MyMeth(int) -- type conversion
        ob.MyMeth(s); // calls ob.MyMeth(int) -- type conversion
        ob.MyMeth(f); // calls ob.MyMeth(double) -- type conversion
    }
}
