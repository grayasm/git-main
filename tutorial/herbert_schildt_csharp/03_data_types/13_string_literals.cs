// Demonstrate escape sequences in strings.
using System;

class StrDemo
{
    static void Main()
    {
        Console.WriteLine("Line One\nLine Two\nLine Three");
        Console.WriteLine("One\tTwo\tThree");
        Console.WriteLine("Four\tFive\tSix");

        // Embed quotes.
        Console.WriteLine("\"Why?\", he asked.");

        // Demonstrate verbatim string literals.
        Console.WriteLine(@"This is a verbatim
string literal
that spans several lines.
");

        Console.WriteLine(@"Here is some tabbed output:
1	2	3	4
5	6	7	8
");

		Console.WriteLine(@"Programmers say, ""I like C#.""");
    }
}
