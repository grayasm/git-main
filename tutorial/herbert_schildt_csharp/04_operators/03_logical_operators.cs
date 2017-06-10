using System;

class Example
{
    static void Main()
    {
        /*
            Operator Meaning
            &        AND
            |        OR
            ^        XOR (exclusive OR)
            ||       Short-circuit OR
            &&       Short-circuit AND
            !        NOT
        */

        bool b1, b2;

        b1 = true;
        b2 = false;

        if(b1 & b2) Console.WriteLine("this won't execute");
        if(!(b1 & b2)) Console.WriteLine("!(b1 & b2) is true");
        if(b1 | b2) Console.WriteLine("b1 | b2 is true");
        if(b1 ^ b2) Console.WriteLine("b1 ^ b2 is true");
    }
}