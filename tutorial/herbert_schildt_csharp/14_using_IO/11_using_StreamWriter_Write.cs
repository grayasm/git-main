// Open a file using StreamWriter.

using System;
using System.IO;


class KtoD
{
    static void Main()
    {
        string str;
        StreamWriter fstr_out = null;

        try
        {
            // Open the file, wrapped in a StreamWriter.
            fstr_out = new StreamWriter("test.txt");
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
            if(fstr_out != null) fstr_out.Close();
        }
    }
}
