// Write and then read back binary data.

using System;
using System.IO;

class RWData
{
    static void Main()
    {
        BinaryWriter dataOut;
        BinaryReader dataIn;

        int i = 10;
        double d = 1023.56;
        bool b = true;
        string str = "This is a test";

        // Open the file for output.
        try
        {
            dataOut =
                new BinaryWriter(new FileStream("testdata", FileMode.Create));
        }
        catch(IOException exc)
        {
            Console.WriteLine("Error Opening File:\n" + exc.Message);
            return;
        }

        // Write data to a file.
        try
        {
            Console.WriteLine("Writing " + i);
            dataOut.Write(i);
            Console.WriteLine("Writing " + d);
            dataOut.Write(d);
            Console.WriteLine("Writing " + b);
            dataOut.Write(b);
            Console.WriteLine("Writing " + 12.2 * 7.4);
            dataOut.Write(12.2 * 7.4);
            Console.WriteLine("Writing " + str);
            dataOut.Write(str);
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error:\n" + exc.Message);
        }
        finally
        {
            dataOut.Close();
        }

        Console.WriteLine();
        // Now, read the data.
        try
        {
            dataIn =
                new BinaryReader(new FileStream("testdata", FileMode.Open));
        }
        catch(IOException exc)
        {
            Console.WriteLine("Error Opening File:\n" + exc.Message);
            return;
        }


        try
        {
            i = dataIn.ReadInt32();
            Console.WriteLine("Reading " + i);
            d = dataIn.ReadDouble();
            Console.WriteLine("Reading " + d);
            b = dataIn.ReadBoolean();
            Console.WriteLine("Reading " + b);
            d = dataIn.ReadDouble();
            Console.WriteLine("Reading " + d);
            str = dataIn.ReadString();
            Console.WriteLine("Reading " + str);
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error:\n" + exc.Message);
        }
        finally
        {
            dataIn.Close();
        }
    }
}
