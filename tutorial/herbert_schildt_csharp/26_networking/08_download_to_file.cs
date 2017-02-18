// Use WebClient to download information into a file.
using System;
using System.Net;
using System.IO;


class WebClientDemo
{
    static void Main()
    {
        WebClient user = new WebClient();

        string uri = "http://www.McGraw-Hill.com";
        string fname = "data.txt";

        try
        {
            Console.WriteLine("Downloading data from " + uri + " to " + fname);
            user.DownloadFile(uri, fname);
        }
        catch (WebException exc)
        {
            Console.WriteLine(exc);
        }

        user.Dispose();
        Console.WriteLine("Download complete.");
    }
}
