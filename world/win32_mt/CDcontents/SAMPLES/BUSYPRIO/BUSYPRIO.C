/*
 * BusyPrio.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This sample is mentioned in the text but there is
 * no associated listing in the book.
 *
 * Demonstrate the effect on performance
 * of using a busy loop that is running
 * in a higher priority thread than the
 * worker thread.
 *
 * Build command: cl /MD busyprio.c
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "MtVerify.h"

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
    HANDLE hThread;
    DWORD exitCode = 0;
    DWORD threadId;
    DWORD begin;
    DWORD elapsed;
    HANDLE hPrimaryThread = GetCurrentThread();

    puts("Timing thread + busy loop...");
    begin = GetTickCount();

    printf("Original priority level of primary thread: %d\n",
            GetThreadPriority(hPrimaryThread));

    SetThreadPriority(hPrimaryThread, THREAD_PRIORITY_HIGHEST);

    printf("New priority level of primary thread: %d\n",
            GetThreadPriority(hPrimaryThread));
    MTVERIFY( hThread = CreateThread(NULL,
        0,
        ThreadFunc,
        (LPVOID)1,
        0,
        &threadId )
    );
    /* This busy loop chews up lots of CPU time */
    for (;;)
    {
        GetExitCodeThread(hThread, &exitCode);
        if ( exitCode != STILL_ACTIVE )
            break;
    }

    elapsed = GetTickCount()-begin;
    printf("Thread + busy loop took: %d.%.03d seconds\n",
                elapsed/1000, elapsed%1000);

    MTVERIFY( CloseHandle(hThread) );

    return EXIT_SUCCESS;
}


/*
 * Cute little busy work routine that computes the value
 * of PI using probability.  Highly dependent on having
 * a good random number generator (rand is iffy)
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    int i;
    int inside = 0;
    double val;

    UNREFERENCED_PARAMETER(n);

    printf("Priority level of worker thread: %d\n",
            GetThreadPriority(GetCurrentThread()));

    /* Seed the random-number generator */
    srand( (unsigned)time( NULL ) );

    for (i=0; i<1000000; i++)
    {
        double x = (double)(rand())/RAND_MAX;
        double y = (double)(rand())/RAND_MAX;
        if ( (x*x + y*y) <= 1.0 )
            inside++;
    }
    val = (double)inside / i;
    printf("PI = %.4g\n", val*4);
    return 0;
}
