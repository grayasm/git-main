// Demonstrate StringReader and StringWriter.

using System;
using System.IO;


class StrRdrWtrDemo
{
    static void Main()
    {
        StringWriter strwtr = null;
        StringReader strrdr = null;

        try
        {
            // Create a StringWriter.
            strwtr = new StringWriter();

            // Write to StringWriter.
            for(int i=0; i < 10; i++)
                strwtr.WriteLine("This is i: " + i);

            // Create a StringReader.
            strrdr = new StringReader(strwtr.ToString());

            // Now, read from StringReader.
            string str = strrdr.ReadLine();

            while(str != null)
            {
                str = strrdr.ReadLine();
                Console.WriteLine(str);
            }
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error\n" + exc.Message);
        }
        finally
        {
            // Release reader and writer resources.
            if(strrdr != null) strrdr.Close();
            if(strwtr != null) strwtr.Close();
        }
    }
}
