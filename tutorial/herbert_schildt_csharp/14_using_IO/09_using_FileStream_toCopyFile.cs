/*
    Copy a file one byte at a time.
    To use this program, specify the name of the source file and the
    destination file. For example, to copy a file called FIRST.DAT to
    a file called SECOND.DAT, use the following command line:

    <program_name> FIRST.DAT SECOND.DAT
*/

using System;
using System.IO;


class CopyFile
{
    static void Main(string[] args)
    {
        int i;
        FileStream fin = null;
        FileStream fout = null;

        if(args.Length != 2)
        {
            Console.WriteLine("Usage: CopyFile From To");
            return;
        }

        try
        {
            // Open the files.
            fin = new FileStream(args[0], FileMode.Open);
            fout = new FileStream(args[1], FileMode.Create);

            // Copy the file.
            do
            {
                i = fin.ReadByte();
                if(i != -1) fout.WriteByte((byte)i);
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
            if(fout != null) fout.Close();
        }
    }
}
