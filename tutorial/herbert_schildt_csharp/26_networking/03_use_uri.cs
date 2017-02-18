// Use Uri.
using System;
using System.Net;


class UriDemo
{
    static void Main()
    {
        Uri sample = new Uri("http://HerbSchildt.com/somefile.txt?SomeQuery");

        Console.WriteLine("Host: " + sample.Host);
        Console.WriteLine("Port: " + sample.Port);
        Console.WriteLine("Scheme: " + sample.Scheme);
        Console.WriteLine("Local Path: " + sample.LocalPath);
        Console.WriteLine("Query: " + sample.Query);
        Console.WriteLine("Path and query: " + sample.PathAndQuery);
    }
}
