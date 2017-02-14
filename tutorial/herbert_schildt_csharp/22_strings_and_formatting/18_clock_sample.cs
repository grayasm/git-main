// A simple clock.
using System;


class SimpleClock
{
    static void Main()
    {
        string t;
        int seconds;
        DateTime dt = DateTime.Now;
        seconds = dt.Second;

        for(;;)
        {
            dt = DateTime.Now;

            // update time if seconds change
            if(seconds != dt.Second)
            {
                seconds = dt.Second;
                t = dt.ToString("T");
                if(dt.Minute==0 && dt.Second==0)
                    t = t + "\a"; // ring bell at top of hour

                Console.WriteLine(t);
            }
        }
    }
}
