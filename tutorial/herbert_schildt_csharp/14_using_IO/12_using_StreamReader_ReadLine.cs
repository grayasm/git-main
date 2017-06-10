// A simple disk-to-screen utility that demonstrates a StreamReader.

using System;
using System.IO;


class DtoS
{
    static void Main()
    {
        FileStream fin;
        string s;

        try
        {
            fin = new FileStream("test.txt", FileMode.Open);
        }
        catch(IOException exc)
        {
            Console.WriteLine("Error Opening file:\n" + exc.Message);
            return ;
        }

        StreamReader fstr_in = new StreamReader(fin);

        try
        {
            while((s = fstr_in.ReadLine()) != null)
            {
                Console.WriteLine(s);
            }
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error:\n" + exc.Message);
        }
        finally
        {
            fstr_in.Close();
        }
    }
}
