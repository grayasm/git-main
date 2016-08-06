                              
                       Sample Programs
                             for
            Multithreading Applications in Win32

                         July, 1997



Chapter Order Sample Listing

This table lists sample programs according to what chapter
they are found in. Most sample programs are character-based
console programs. Those programs that are graphically-based
are marked in the table below as GUI. The notes also mention
those samples that are C++, MFC or only work under Windows
NT.

The table in in the next section is in alphabetical order
and gives short descriptions of the various sample programs.


            Sample Name  Listing  Notes

Chapter 2   Numbers       2-1                      
            ExitCode      2-2                      
            ExitThrd      2-3                      
            Error         2-4                      
            BackPrnt      2-6                      
Chapter 3   BusyWait      3-1                      
            TaskQueS      3-2                      
            TaskQueM      3-3                      
            PrntWait      3-5      GUI
Chapter 4   Dining                 GUI
            EventTst               GUI
Chapter 5   ThrdTerm      5-1                      
            BusyPrio                              
Chapter 6   IoByFile      6-1      NT Only
            IoByEvnt      6-2      NT Only
            IoByAPC       6-3      NT Only
            Echo          6-4      NT Only
Chapter 7   Readwrit      7-1                      
Chapter 8   SrchCrt       8-1                      
            SrchWin       8-2                      
            Banner        8-3                      
Chapter 9   CppSkel       9-1      C++
            BadClass      9-2      C++
            Member        9-3      C++
Chapter 10  Numbers.cpp                           
            Numbers2                              
            NumClass                              
Chapter 11  Cancel                 GUI, MFC, C++
Chapter 13  CopyData      13-1     GUI, MFC, C++
            ShareMem      13-3     GUI, MFC, C++
Chapter 14  SmallDll      14-1     C++
            Worker        14-3     C++
Chapter 16  is2odbc                C++, ISAPI
Chapter 17  ComDemo                C++, NT Only, OLE

==========================================================


                                                  
Alphabetical Order Sample Descriptions


  Sample      Chapter                  Notes
  Name
                                      
BackPrnt    Chapter 2 (Listing 2-6)   GUI
            Background printing example. Italicizes the
            given text and displays it on either the screen
            on prints to the printer. Can have multiple
            jobs outstanding at the same time.
            
BadClass    Chapter 9 (Listing 9-2)   C++
            Demonstrates how *not* to start a thread with a
            C++ member function. This sample program does
            not compile.
            
Banner      Chapter 8 (Listing 8-3)             
            Demonstrates the use the Console API to run
            multiple threads without using the run-time
            library and stdio.
            
BusyPrio    Chapter 5                           
            Demonstrates the impact that high priority
            threads can have on a running program.
            
BusyWait    Chapter 3 (Listing 3-1)             
            Demonstrates the impact of a busy loop on
            program performance.
            
Busy2,      Chapter 3                           
Busy3       Variations on BusyWait to be used with
            Performance Monitor.
            
Cancel      Chapter 11                 GUI, MFC, C++
            Shows two techniques that were tried to run a
            modeless dialog concurrently with the primary
            thread. This sample shows techniques that do
            not work.
            
ComDemo     Chapter 17                   C++, NT Only, OLE
            Freethreading model OLE server (dual-
            interface). Included with this sample are
            MfcCli and VbCli, which are clients to test the
            server written in MFC and Visual Basic,
            respectively.
            
CopyData    Chapter 13 (Listing 13-1)  GUI, MFC, C++
            Demonstrates interprocess communication using
            the WM_COPYDATA message.
            
CppSkel     Chapter 9 (Listing 9-1)   C++
            Show how to work around the problems of using
            _beginthreadex() in a C++ program.
            
Dining      Chapter 4                 GUI
            Graphically illustrates deadlock using the
            Dining Philosophers.
            
Echo        Chapter 6 (Listing 6-4)   NT Only
            Echo server written using WinSock and I/O
            completion ports. Demonstrates the optimal way
            to write high performance server applications.
            There are two subdirectories, EchoSrv and
            EchoCli. Run EchoSrv in one window and the
            EchoCli in another window.
            
Error       Chapter 2 (Listing 2-4)             
            Demonstrates MTVERIFY catching a program error.
            
EventTst    Chapter 4                 GUI
            Lets you can control an Event Object and shows
            the results of threads waiting on the event
            object.
            
ExitCode    Chapter 2 (Listing 2-2)             
            Use GetExitCodeThread() to decide if a thread
            has exited.
            
ExitThrd    Chapter 2 (Listing 2-3)             
            Show ExitThread() in action.
            
IoByAPC     Chapter 6 (Listing 6-2)   NT Only
            Demonstrates overlapped I/O using Asynchronous
            Procedure Calls.
            
IoByEvnt    Chapter 6 (Listing 6-2)   NT Only
            Demonstrates overlapped I/O that waits by using
            an event object.
            
IoByFile    Chapter 6 (Listing 6-1)   NT Only
            Demonstrates overlapped I/O that waits by using
            the file handle.
            
Is2odbc     Chapter 16                C++, ISAPI
            ISAPI plug-in for Internet Information Server
            and Peer Web Services that allows ISAPI to
            access a JET database. This sample requires
            extensive configuration; see the README in this
            directory.
            
Member      Chapter 9 (Listing 9-3)   C++
            How to use a class member function to start a
            thread.
            
Numbers     Chapter 2 (Listing 2-1)             
            Shows the problems that can be caused by
            running multiple threads. This sample
            intentionally does not use the multithreaded C
            run-time library.
            
Numbers.cpp Chapter 10                          
            Rewrite of the Numbers sample program from
            Chapter 2. This version uses MFC.
            
Numbers2    Chapter 10                          
            Update of Numbers.cpp that shows finer control
            over the thread object.
            
NumClass    Chapter 10                          
            Start an MFC worker thread without using
            AfxBeginThread().
            
PrntWait    Chapter 3 (Listing 3-5)   GUI
            Continuation of BackPrnt. Monitors currently
            running threads to give a current count and
            uses WaitForMultipleObjects() to wait for
            threads to terminate before exiting.
            
Readwrit    Chapter 7                           
            Uses a Readers/Writers lock to protect a linked
            list.
            
ShareMem    Chapter 13                 GUI, MFC, C++
            Uses shared memory in the paging file to
            perform low-level interprocess communication.
            
SmallDll    Chapter 14                C++
            DLL and driver programs that illustrate the
            attach and detach messages that a DLL receives
            as a process and its threads invoke the DLL.
            
SrchCrt     Chapter 8                           
            Searches through *.c in the current directory
            using multiple threads. Uses the C run-time
            library.
            
SrchWin     Chapter 8                           
            Searches through *.c in the current directory
            using multiple threads. Does not use the C run-
            time library, so can call CreateThread().
            
TaskQueM    Chapter 3                           
            Queue a set of tasks for a pool of threads
            using WaitForMultipleObjects(). This solution
            is much more optimal than TaskQueS.
            
TaskQueS    Chapter 3                           
            Queue a set of tasks for a pool of threads
            using WaitForSingleObject(). This solution is
            much less optimal than TaskQueM.
            
ThrdTerm    Chapter 5                           
            How to cleanly cause a thread to exit.
            
Worker      Chapter 14                C++
            How to use the message queue as a request queue
            for worker threads.
            

