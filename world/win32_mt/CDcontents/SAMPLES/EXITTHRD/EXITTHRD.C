/*
 * ExitThrd.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 2, Listing 2-3
 *
 * Demonstrate ExitThread
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID);
void AnotherFunc(void);

int main()
{
    HANDLE hThrd;
    DWORD exitCode = 0;
    DWORD threadId;
    
    hThrd = CreateThread(NULL,
        0,
        ThreadFunc,
        (LPVOID)1,
        0,
        &threadId );
    if (hThrd)
        printf("Thread launched\n");

    for(;;)
    {
        BOOL rc;
        rc = GetExitCodeThread(hThrd, &exitCode);
        if (rc && exitCode != STILL_ACTIVE )
            break;
    }

    CloseHandle(hThrd);

    printf("Thread returned %d\n", exitCode);

    return EXIT_SUCCESS;
}


/*
 * Call a function to do something that terminates
 * the thread with ExitThread instead of returning.
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    printf("Thread running\n");
    AnotherFunc();
    return 0;
}

void AnotherFunc()
{
    printf("About to exit thread\n");
    ExitThread(4);
    // It is impossible to get here, this line
    // will never be printed
    printf("This will never print\n");
}
