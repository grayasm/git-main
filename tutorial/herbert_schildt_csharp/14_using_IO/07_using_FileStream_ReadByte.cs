/*
    In some situations, it may be easier to wrap the portions of a program
    that open the file and access the file within a single try block
    rather than separating the two.

    Display a text file. Compact version.
*/

using System;
using System.IO;


class ShowFile
{
    static void Main(string[] args)
    {
        int i;
        FileStream fin = null;

        if(args.Length != 1)
        {
            Console.WriteLine("Usage: ShowFile File");
            return;
        }

        // Use a single try block to open the file and then
        // read from it.
        try
        {
            fin = new FileStream(args[0], FileMode.Open);
            // Read bytes until EOF is encountered.

            do
            {
                i = fin.ReadByte();
                if(i != -1) Console.Write((char) i);
            }
            while(i != -1);

        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error:\n" + exc.Message);
        }
        finally
        {
            if(fin != null) fin.Close();
        }
    }
}
