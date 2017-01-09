using System;

class Example
{
    static void Main()
    {
        /*
        Operator Meaning
        +        Addition
        –        Subtraction (also unary minus)
        *        Multiplication
        /        Division
        %        Modulus
        ++       Increment
        --       Decrement
        */


        // Demonstrate the % operator.
        int iresult, irem;
        double dresult, drem;

        iresult = 10 / 3;
        irem = 10 % 3;
        dresult = 10.0 / 3.0;
        drem = 10.0 % 3.0;

        Console.WriteLine("Result and remainder of 10 / 3: " +
                          iresult + " " + irem);

        Console.WriteLine("Result and remainder of 10.0 / 3.0: " +
                          dresult + " " + drem);


        // Increment and Decrement
        int xii = 100;
        xii = xii + 1;
        xii++; // postfix form
        ++xii; // prefix form


        // Demonstrate the difference between prefix and
        // postfix forms of ++.

        int x, y;
        int i;
        x = 1;
        y = 0;

        Console.WriteLine("Series generated using y = y + x++;");
        for(i = 0; i < 10; i++)
        {
            y = y + x++; // postfix ++
            Console.WriteLine(y + " ");
        }

        Console.WriteLine();
        x = 1;
        y = 0;
        Console.WriteLine("Series generated using y = y + ++x;");
        for(i = 0; i < 10; i++)
        {
            y = y + ++x; // prefix ++
            Console.WriteLine(y + " ");
        }
        Console.WriteLine();
    }
}