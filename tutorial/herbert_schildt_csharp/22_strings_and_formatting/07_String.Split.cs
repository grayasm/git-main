// Tokenize strings.
using System;


class TokenizeDemo
{
    static void Main()
    {
        string[] input = {
                           "100 + 19",
                           "100 / 3.3",
                           "-3 * 9",
                           "100 - 87"
                         };

        char[] seps = {' '};
        for(int i=0; i < input.Length; i++)
        {
            // split string into parts
            string[] parts = input[i].Split(seps);
            Console.Write("Command: ");

            for(int j=0; j < parts.Length; j++)
                Console.Write(parts[j] + " ");

            Console.Write(", Result: ");
            double n = Double.Parse(parts[0]);
            double n2 = Double.Parse(parts[2]);

            switch(parts[1])
            {
            case "+":
                Console.WriteLine(n + n2);
                break;

            case "-":
                Console.WriteLine(n - n2);
                break;

            case "*":
                Console.WriteLine(n * n2);
                break;

            case "/":
                Console.WriteLine(n / n2);
                break;
            }
        }
    }
}