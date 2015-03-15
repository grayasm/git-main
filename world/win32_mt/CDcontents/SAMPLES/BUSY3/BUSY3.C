/*
 * Busy3.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This sample is mentioned in the text but there is
 * no associated listing in the book.
 *
 * Use a busy loop to wait on a thread
 * that is sleeping.  This sample should
 * be used in conjunction with the
 * performance meter in Windows NT.
 *
 * Build command: cl /MD busy3.c
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
    HANDLE hThrd;
    DWORD exitCode = 0;
    DWORD threadId;

    puts("Waiting...");

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

    printf("Finished.\n");

    MTVERIFY( CloseHandle(hThrd) );

    return EXIT_SUCCESS;
}


DWORD WINAPI ThreadFunc(LPVOID n)
{
    UNREFERENCED_PARAMETER(n);

    Sleep(60);
    return 0;
}
