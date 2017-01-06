using System;

class Example
{
    static void Main()
    {
        /*
            Operator Meaning
            ==       Equal to
            !=       Not equal to
            >        Greater than
            <        Less than
            >=       Greater than or equal to
            <=       Less than or equal to
        */

        int i, j;
        bool b1, b2;

        i = 10;
        j = 11;

        if(i < j) Console.WriteLine("i < j");
        if(i <= j) Console.WriteLine("i <= j");
        if(i != j) Console.WriteLine("i != j");
        if(i == j) Console.WriteLine("this won't execute");
        if(i >= j) Console.WriteLine("this won't execute");
        if(i > j) Console.WriteLine("this won't execute");
    }
}