/*

// General form for overloading a unary operator
public static ret-type operator op(param-type operand)
{
 // operations
}

// General form for overloading a binary operator
public static ret-type operator op(param-type1 operand1,
                                   param-type1 operand2)
{
 // operations
}
*/


using System;

class Integer
{
    int m;

    public Integer(int i) { m = i; }
    public static int operator + (Integer l, Integer r)
    {
        /* because of static type, this function cannot access m,
           so only solution is to make it binary operator. */

        int result = l.m + r.m;
        return result;
    }
}

class Ex
{
    static void Main()
    {
        Integer i100 = new Integer(100);
        Integer i200 = new Integer(200);

        Console.WriteLine ("i100+i200 = " + (i100 + i200));
    }
}