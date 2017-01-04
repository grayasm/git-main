// pag 33, Semicolons, Positioning and Identation

using System;

class Example
{
    static void Main()
    {
        int x, y, z;

        x = 10; y = 10; z = 10;

        // C# does not recognize the end of the line as the end of a
        // statement—only a semicolon terminates a statement.

        x = y;
        y = y + 1;
        Console.WriteLine(x + " " + y);

        // is the same as

        x = y; y = y + 1; Console.WriteLine(x + " " + y);

        // the following is perfectly acceptable

        Console.WriteLine("This is a long line of output " +
                           x + y + z +
                           " more output");
    }
}
