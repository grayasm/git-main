/*  Examine Cookies.

    To see what cookies a website uses,
    specify its name on the command line.
    For example, if you call this program
    CookieDemo, then

        CookieDemo http://msn.com

    displays the cookies associated with msn.com.
*/


using System;
using System.Net;


class CookieDemo
{
    static void Main(string[] args)
    {
        if(args.Length != 1)
        {
            Console.WriteLine("Usage: CookieDemo <uri>");
            return ;
        }


        // Create a WebRequest to the specified URI.
        HttpWebRequest req = (HttpWebRequest)
        WebRequest.Create(args[0]);

        // Get an empty cookie container.
        req.CookieContainer = new CookieContainer();

        // Send the request and return the response.
        HttpWebResponse resp = (HttpWebResponse)
        req.GetResponse();

        // Display the cookies.
        Console.WriteLine("Number of cookies: " + resp.Cookies.Count);
        Console.WriteLine("{0,-20}{1}", "Name", "Value");

        for(int i=0; i < resp.Cookies.Count; i++)
            Console.WriteLine("{0, -20}{1}",
                              resp.Cookies[i].Name,
                              resp.Cookies[i].Value);

        // Close the Response.
        resp.Close();
    }
}
