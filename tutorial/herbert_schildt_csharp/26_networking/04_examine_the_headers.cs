// Examine the headers.
using System;
using System.Net;


class HeaderDemo
{
    static void Main()
    {
        // Create a WebRequest to a URI.
        HttpWebRequest req = (HttpWebRequest)
        WebRequest.Create("http://www.McGraw-Hill.com");

        // Send that request and return the response.
        HttpWebResponse resp = (HttpWebResponse)
        req.GetResponse();

        // Obtain a list of the names.
        string[] names = resp.Headers.AllKeys;

        // Display the header name/value pairs.
        Console.WriteLine("{0,-20}{1}\n", "Name", "Value");
        foreach(string n in names)
        {
            Console.Write("{0,-20}", n);
            foreach(string v in resp.Headers.GetValues(n))
                Console.WriteLine(v);
        }

        // Close the Response.
        resp.Close();
    }
}
