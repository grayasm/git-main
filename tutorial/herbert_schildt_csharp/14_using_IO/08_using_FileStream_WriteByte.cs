// Write to a file.

using System;
using System.IO;


class WriteToFile
{
    static void Main(string[] args)
    {
        FileStream fout = null;

        try
        {
            // Open output file.
            fout = new FileStream("test.txt", FileMode.CreateNew);

            // Write the alphabet to the file.
            for(char c = 'A'; c <= 'Z'; c++)
                fout.WriteByte((byte) c);
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error:\n" + exc.Message);
        }
        finally
        {
            if(fout != null) fout.Close();
        }
    }
}
