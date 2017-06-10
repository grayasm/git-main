using System;

class IdTest
{
    static void Main()
    {
        int @if; // use if as an identifier

        for(@if = 0; @if < 10; @if++)
                Console.WriteLine("@if is " + @if);
    }
}
