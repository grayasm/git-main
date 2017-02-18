/*
    MiniCrawler: A skeletal Web crawler.
    Usage:
    To start crawling, specify a starting
    URI on the command line. For example,
    to start at McGraw-Hill.com use this
    command line:

    MiniCrawler http://McGraw-Hill.com
*/

using System;
using System.Net;
using System.IO;


class MiniCrawler
{
    // Find a link in a content string.
    static string FindLink(string htmlstr, ref int startloc)
    {
        int i;
        int start, end;
        string uri = null;

        i = htmlstr.IndexOf("href=\"http",
                            startloc,
                            StringComparison.OrdinalIgnoreCase);

        if(i != -1)
        {
            start = htmlstr.IndexOf('"', i) + 1;
            end = htmlstr.IndexOf('"', start);
            uri = htmlstr.Substring(start, end-start);
            startloc = end;
        }
        return uri;
    }

    static void Main(string[] args)
    {
        string link = null;
        string str;
        string answer;
        int curloc; // holds current location in response

        if(args.Length != 1)
        {
            Console.WriteLine("Usage: MiniCrawler <uri>");
            return ;
        }

        string uristr = args[0]; // holds current URI
        HttpWebResponse resp = null;

        try
        {
            do
            {
                Console.WriteLine("Linking to " + uristr);

                // Create a WebRequest to the specified URI.
                HttpWebRequest req = (HttpWebRequest)
                WebRequest.Create(uristr);
                uristr = null; // disallow further use of this URI

                // Send that request and return the response.
                resp = (HttpWebResponse) req.GetResponse();

                // From the response, obtain an input stream.
                Stream istrm = resp.GetResponseStream();

                // Wrap the input stream in a StreamReader.
                StreamReader rdr = new StreamReader(istrm);

                // Read in the entire page.
                str = rdr.ReadToEnd();
                curloc = 0;
                do
                {
                    // Find the next URI to link to.
                    link = FindLink(str, ref curloc);

                    if(link != null)
                    {
                        Console.WriteLine("Link found: " + link);
                        Console.Write("Link, More, Quit?");
                        answer = Console.ReadLine();

         if(string.Equals(answer, "L", StringComparison.OrdinalIgnoreCase))
                        {
                            uristr = string.Copy(link);
                            break;
                        }
         else if(string.Equals(answer, "Q", StringComparison.OrdinalIgnoreCase))
                        {
                            break;
                        }
         else if(string.Equals(answer, "M", StringComparison.OrdinalIgnoreCase))
                        {
                            Console.WriteLine("Searching for another link.");
                        }
                    }
                    else
                    {
                        Console.WriteLine("No link found.");
                        break;
                    }
                }
                while(link.Length > 0);


                // Close the Response.
                if(resp != null)
                    resp.Close();

            }
            while(uristr != null);

        }
        catch(WebException exc)
        {
            Console.WriteLine("Network Error: " + exc.Message +
                              "\nStatus code: " + exc.Status);
        }
        catch(ProtocolViolationException exc)
        {
            Console.WriteLine("Protocol Error: " + exc.Message);
        }
        catch(UriFormatException exc)
        {
            Console.WriteLine("URI Format Error: " + exc.Message);
        }
        catch(NotSupportedException exc)
        {
            Console.WriteLine("Unknown Protocol: " + exc.Message);
        }
        catch(IOException exc)
        {
            Console.WriteLine("I/O Error: " + exc.Message);
        }
        finally
        {
            if(resp != null)
                resp.Close();
        }

        Console.WriteLine("Terminating MiniCrawler.");
    }
}
