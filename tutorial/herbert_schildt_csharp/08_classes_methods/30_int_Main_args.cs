// Encode or decode a message using a simple substitution cipher.

using System;


class Cipher
{
    static int Main(string[] args)
    {
        // See if arguments are present.
        if(args.Length < 2)
        {
            Console.WriteLine("Usage: encode/decode word1 [word2...wordN]");
            return 1; // return failure code
        }

        // If args present, first arg must be encode or decode.
        if(args[0] != "encode" & args[0] != "decode")
        {
            Console.WriteLine("First arg must be encode or decode.");
            return 1; // return failure code
        }

        // Encode or decode message.
        for(int n=1; n < args.Length; n++)
        {
            for(int i=0; i < args[n].Length; i++)
            {
                if(args[0] == "encode")
                    Console.Write((char) (args[n][i] + 1) );
                else
                    Console.Write((char) (args[n][i] - 1) );
            }

            Console.Write(" ");
        }

        Console.WriteLine();
        return 0;
    }
}
