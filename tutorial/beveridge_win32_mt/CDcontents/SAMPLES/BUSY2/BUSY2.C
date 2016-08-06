/*
 * Busy2.c
 *
 * Sample code for Multithreading Applications in Win32
 * This sample is mentioned in the text but there is
 * no associated listing in the book.
 *
 * Run a busy loop and a worker thread at
 * the same time. This program is intended
 * to be monitored by PerfMon in Windows NT.
 * You will need to Ctrl-C out to exit.
 *
 * Build command: cl /MD busywait.c
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
    HANDLE hThrd;
    DWORD exitCode = 0;
    DWORD threadId;
    DWORD begin;
    DWORD elapsed;

    puts("Busy2 is designed to use up CPU time.");
    puts("Press Ctrl+C to exit.");
    begin = GetTickCount();

    MTVERIFY( hThrd = CreateThread(NULL,
        0,
        ThreadFunc,
        (LPVOID)1,
        0,
        &threadId )
    );
    /* This busy loop chews up lots of CPU time */
    for (;;)
    {
        GetExitCodeThread(hThrd, &exitCode);
        if ( exitCode != STILL_ACTIVE )
            break;
    }

    elapsed = GetTickCount()-begin;
    printf("Thread + busy loop took: %d.%.03d seconds\n",
                elapsed/1000, elapsed%1000);

    MTVERIFY( CloseHandle(hThrd) );

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

    /* Seed the random-number generator */
    srand( (unsigned)time( NULL ) );

    for (i=0; i<100000000; i++)
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
