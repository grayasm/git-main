/*
    Use BinaryReader and BinaryWriter to implement a simple inventory program.
*/

using System;
using System.IO;


class Inventory
{
    static void Main()
    {
        BinaryWriter dataOut;
        BinaryReader dataIn;

        string item; // name of item
        int onhand; // number on hand
        double cost; // cost

        try
        {
            dataOut = new BinaryWriter(new FileStream("inventory.dat",
                                       FileMode.Create));
        }
        catch(IOException exc)
        {
            Console.WriteLine("Cannot Open Inventory File For Output");
            Console.WriteLine("Reason: " + exc.Message);
            return;
        }

        // Write some inventory data to the file.
        try
        {
            dataOut.Write("Hammers");
            dataOut.Write(10);
            dataOut.Write(3.95);
            dataOut.Write("Screwdrivers");
            dataOut.Write(18);
            dataOut.Write(1.50);
            dataOut.Write("Pliers");
            dataOut.Write(5);
            dataOut.Write(4.95);
            dataOut.Write("Saws");
            dataOut.Write(8);
            dataOut.Write(8.95);
        }
        catch(IOException exc)
        {
            Console.WriteLine("Error Writing Inventory File");
            Console.WriteLine("Reason: " + exc.Message);
        }
        finally
        {
            dataOut.Close();
        }

        Console.WriteLine();


        // Now, open inventory file for reading.
        try
        {
            dataIn = new BinaryReader(new FileStream("inventory.dat",
                                      FileMode.Open));
        }
        catch(IOException exc)
        {
            Console.WriteLine("Cannot Open Inventory File For Input");
            Console.WriteLine("Reason: " + exc.Message);
            return;
        }

        // Look up item entered by user.
        Console.Write("Enter item to look up: ");
        string what = Console.ReadLine();
        Console.WriteLine();

        try
        {
            for(;;)
            {
                // Read an inventory entry.
                item = dataIn.ReadString();
                onhand = dataIn.ReadInt32();
                cost = dataIn.ReadDouble();

                // See if the item matches the one requested.
                // If so, display information.
                if(item.Equals(what, StringComparison.OrdinalIgnoreCase))
                {
                    Console.WriteLine(onhand + " " + item + " on hand. " +
                                      "Cost: {0:C} each", cost);

                    Console.WriteLine("Total value of {0}: {1:C}." ,
                                      item, cost * onhand);
                    break;
                }
            }
        }
        catch(EndOfStreamException)
        {
            Console.WriteLine("Item not found.");
        }
        catch(IOException exc)
        {
            Console.WriteLine("Error Reading Inventory File");
            Console.WriteLine("Reason: " + exc.Message);
        }
        finally
        {
            dataIn.Close();
        }
    }
}
