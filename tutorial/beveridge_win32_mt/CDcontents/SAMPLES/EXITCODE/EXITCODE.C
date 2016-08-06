/*
 * ExitCode.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 2, Listing 2-2
 *
 * Start two threads and try to exit
 * when the user presses a key.
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
    HANDLE hThrd1;
    HANDLE hThrd2;
    DWORD exitCode1 = 0;
    DWORD exitCode2 = 0;
    DWORD threadId;
    
    hThrd1 = CreateThread(NULL,
        0,
        ThreadFunc,
        (LPVOID)1,
        0,
        &threadId );
    if (hThrd1)
        printf("Thread 1 launched\n");

    hThrd2 = CreateThread(NULL,
        0,
        ThreadFunc,
        (LPVOID)2,
        0,
        &threadId );
    if (hThrd2)
        printf("Thread 2 launched\n");


    // Keep waiting until both calls to
    // GetExitCodeThread succeed AND
    // neither of them returns STILL_ACTIVE.
    // This method is not optimal - we'll
    // see the correct way in Chapter 3.
    for (;;)
    {
        printf("Press any key to exit..\n");
        getch();

        GetExitCodeThread(hThrd1, &exitCode1);
        GetExitCodeThread(hThrd2, &exitCode2);
        if ( exitCode1 == STILL_ACTIVE )
            puts("Thread 1 is still running!");
        if ( exitCode2 == STILL_ACTIVE )
            puts("Thread 2 is still running!");
        if ( exitCode1 != STILL_ACTIVE
            && exitCode2 != STILL_ACTIVE )
            break;
    }

    CloseHandle(hThrd1);
    CloseHandle(hThrd2);

    printf("Thread 1 returned %d\n", exitCode1);
    printf("Thread 2 returned %d\n", exitCode2);

    return EXIT_SUCCESS;
}


/*
 * Take the startup value, do some simple math on it,
 * and return the calculated value.
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    Sleep((DWORD)n*1000*2);
    return (DWORD)n * 10;
}
