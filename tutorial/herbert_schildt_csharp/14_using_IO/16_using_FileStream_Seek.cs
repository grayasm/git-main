// Demonstrate random access.

using System;
using System.IO;


class RandomAccessDemo
{
    static void Main()
    {
        FileStream f = null;
        char ch;

        try
        {
            f = new FileStream("random.dat", FileMode.Create);

            // Write the alphabet.
            for(int i=0; i < 26; i++)
                f.WriteByte((byte)('A'+i));

            // Now, read back specific values.
            f.Seek(0, SeekOrigin.Begin); // seek to first byte
            ch = (char) f.ReadByte();
            Console.WriteLine("First value is " + ch);

            f.Seek(1, SeekOrigin.Begin); // seek to second byte
            ch = (char) f.ReadByte();
            Console.WriteLine("Second value is " + ch);

            f.Seek(4, SeekOrigin.Begin); // seek to 5th byte
            ch = (char) f.ReadByte();
            Console.WriteLine("Fifth value is " + ch);
            Console.WriteLine();

            // Now, read every other value.
            Console.WriteLine("Here is every other value: ");
            for(int i=0; i < 26; i += 2)
            {
                f.Seek(i, SeekOrigin.Begin); // seek to ith character
                ch = (char) f.ReadByte();
                Console.Write(ch + " ");
            }
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error\n" + exc.Message);
        }
        finally
        {
            if(f != null) f.Close();
        }
        Console.WriteLine();
    }
}
