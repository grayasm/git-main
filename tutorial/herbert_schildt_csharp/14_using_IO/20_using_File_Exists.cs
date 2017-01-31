// Use Exists() and GetLastAccessTime().

using System;
using System.IO;


class ExistsDemo
{
    static void Main()
    {
        if(File.Exists("test.txt"))
        {
            Console.WriteLine("File exists. It was last accessed at " +
                              File.GetLastAccessTime("test.txt"));
        }
        else
            Console.WriteLine("Does Not Exist");
    }
}
