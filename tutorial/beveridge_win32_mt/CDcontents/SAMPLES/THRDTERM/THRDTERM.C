/*
 * ThrdTerm.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 5, Listing 5-1
 *
 * Demonstrates how to request threads to exit.
 *
 * Build command: cl /MD ThrdTerm.c
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "MtVerify.h"

DWORD WINAPI ThreadFunc(LPVOID);

HANDLE hRequestExitEvent = FALSE;

int main()
{
    HANDLE hThreads[2];
    DWORD dwThreadId;
    DWORD dwExitCode = 0;
    int i;

    hRequestExitEvent = CreateEvent(
        NULL, TRUE, FALSE, NULL);

    for (i=0; i<2; i++)
        MTVERIFY( hThreads[i] = CreateThread(NULL,
            0,
            ThreadFunc,
            (LPVOID)i,
            0,
            &dwThreadId )
        );

    // Wait around for awhile, make
    // sure the thread is running.
    Sleep(1000);

    SetEvent(hRequestExitEvent);
    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

    for (i=0; i<2; i++)
        MTVERIFY( CloseHandle(hThreads[i]) );

    return EXIT_SUCCESS;
}


DWORD WINAPI ThreadFunc(LPVOID p)
{
    int i;
    int inside = 0;

    UNREFERENCED_PARAMETER(p);

    /* Seed the random-number generator */
    srand( (unsigned)time( NULL ) );

    for (i=0; i<1000000; i++)
    {
        double x = (double)(rand())/RAND_MAX;
        double y = (double)(rand())/RAND_MAX;
        if ( (x*x + y*y) <= 1.0 )
            inside++;
        if (WaitForSingleObject(hRequestExitEvent, 0) != WAIT_TIMEOUT)
        {
            printf("Received request to terminate\n");
            return (DWORD)-1;
        }
    }
    printf("PI = %.4g\n", (double)inside / i * 4);
    return 0;
}
