// Handle network exceptions.
using System;
using System.Net;
using System.IO;


class NetExcDemo
{
    static void Main()
    {
        int ch;
        try
        {
            // First, create a WebRequest to a URI.
            HttpWebRequest req = (HttpWebRequest)
            WebRequest.Create("http://www.McGraw-Hill.com");

            // Next, send that request and return the response.
            HttpWebResponse resp = (HttpWebResponse)
            req.GetResponse();

            // From the response, obtain an input stream.
            Stream istrm = resp.GetResponseStream();

            /* Now, read and display the html present at
               the specified URI. So you can see what is
               being displayed, the data is shown
               400 characters at a time. After each 400
               characters are displayed, you must press
               ENTER to get the next 400. */

            for(int i=1; ; i++)
            {
                ch = istrm.ReadByte();
                if(ch == -1)
                    break;

                Console.Write((char) ch);
                if((i%400)==0)
                {
                    Console.Write("\nPress Enter.");
                    Console.ReadLine();
                }
            }

            // Close the Response. This also closes istrm.
            resp.Close();
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
        catch(System.Security.SecurityException exc)
        {
            Console.WriteLine("Security Exception: " + exc.Message);
        }
        catch(InvalidOperationException exc)
        {
            Console.WriteLine("Invalid Operation: " + exc.Message);
        }
    }
}
