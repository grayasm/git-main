using System;




class Jagged
{
    static void Main()
    {
        // Demonstrate an implicitly typed jagged array.

        var jagged = new[] {
                            new[] { 1, 2, 3, 4 },
                            new[] { 9, 8, 7 },
                            new[] { 11, 12, 13, 14, 15 }
                           };

        for(int j = 0; j < jagged.Length; j++)
        {
            for(int i=0; i < jagged[j].Length; i++)
                Console.Write(jagged[j][i] + " ");

            Console.WriteLine();
        }

    }
}