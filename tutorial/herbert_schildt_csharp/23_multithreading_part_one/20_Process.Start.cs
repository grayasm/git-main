/*
    Starting a Separate Task.

    Besides thread-based multitasking there is also process-based multitasking.
    In C# you do this with Process class, defined within System.Diagnostics
    namespace. To start another process use Start( ) method defined by Process.
    Here is one of its simplest forms:

public static Process Start(string fileName)

    When a process that you create ends, call Close( ) to free the memory
    associated with that process. It is shown here:

public void Close( )

    You can terminate a process in two ways. If the process is a Windows
    GUI application, then to terminate the process, call CloseMainWindow( ),
    shown here:

public bool CloseMainWindow( )

    To positively terminate a process, call Kill( ), as shown here:

public void Kill( )

*/


// Starting a new process.
using System;
using System.Diagnostics;


class StartProcess
{
    static void Main()
    {
        Process newProc = Process.Start("wordpad.exe");

        Console.WriteLine("New process started.");

        newProc.WaitForExit();

        newProc.Close(); // free resources

        Console.WriteLine("New process ended.");
    }
}
