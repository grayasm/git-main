// A simple key-to-disk utility that demonstrates a StreamWriter.

using System;
using System.IO;


class KtoD
{
    static void Main()
    {
        string str;
        FileStream fout;

        // First, open the file stream.
        try
        {
            fout = new FileStream("test.txt", FileMode.Create);
        }
        catch(IOException exc)
        {
            Console.WriteLine("Error Opening File:\n" + exc.Message);
            return ;
        }

        // Wrap the file stream in a StreamWriter.
        StreamWriter fstr_out = new StreamWriter(fout);
        try
        {
            Console.WriteLine("Enter text ('stop' to quit).");
            do
            {
                Console.Write(": ");
                str = Console.ReadLine();

                if(str != "stop")
                {
                    str = str + "\r\n"; // add newline
                    fstr_out.Write(str);
                }
            }
            while(str != "stop");
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error:\n" + exc.Message);
        }
        finally
        {
            fstr_out.Close();
        }
    }
}
