/*
 * Main1.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 14, Listing 14-2
 *
 * Driver to load the simple DLL, create a
 * thread, call a function in the DLL, and exit.
 */
 
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

 
_declspec(dllimport) BOOL TheFunction();
DWORD WINAPI ThreadFunc(LPVOID);

VOID main(VOID) 
{ 
    HANDLE  hThrd;
    DWORD   dwThreadId;
 
    hThrd = CreateThread(NULL,
        0,
        ThreadFunc,
        NULL,
        0,
        &dwThreadId );
    if (hThrd)
        printf("\tThread launched\n");
 
    WaitForSingleObject(hThrd, INFINITE);
    CloseHandle(hThrd);
} 
 
/*
 * Just call a function in the DLL and exit
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    printf("\tThread running\n");

    TheFunction();

    return 0;
}

