/*
    For the numeric types, the .NET structure names and their C# keyword
    equivalents are given here:

    .NET Structure Name     C# Name         Conversion Method
    Decimal                 decimal         static decimal Parse(string s)
    Double                  double          static double  Parse(string s)
    Single                  float           static float   Parse(string s)
    Int16                   short           static short   Parse(string s)
    Int32                   int             static int     Parse(string s)
    Int64                   long            static long    Parse(string s)
    UInt16                  ushort          static ushort  Parse(string s)
    UInt32                  uint            static uint    Parse(string s)
    UInt64                  ulong           static ulong   Parse(string s)
    Byte                    byte            static byte    Parse(string s)
    SByte                   sbyte           static sbyte   Parse(string s)
*/


// This program averages a list of numbers entered by the user.

using System;
using System.IO;


class AvgNums
{
    static void Main()
    {
        string str;
        int n;
        double sum = 0.0;
        double avg, t;

        Console.Write("How many numbers will you enter: ");
        str = Console.ReadLine();

        try
        {
            n = Int32.Parse(str);
        }
        catch(FormatException exc)
        {
            Console.WriteLine(exc.Message);
            return;
        }
        catch(OverflowException exc)
        {
            Console.WriteLine(exc.Message);
            return;
        }

        Console.WriteLine("Enter " + n + " values.");
        for(int i=0; i < n ; i++)
        {
            Console.Write(": ");
            str = Console.ReadLine();
            try
            {
                t = Double.Parse(str);
            }
            catch(FormatException exc)
            {
                Console.WriteLine(exc.Message);
                t = 0.0;
            }
            catch(OverflowException exc)
            {
                Console.WriteLine(exc.Message);
                t = 0;
            }

            sum += t;
        }

        avg = sum / n;
        Console.WriteLine("Average is " + avg);
    }
}
