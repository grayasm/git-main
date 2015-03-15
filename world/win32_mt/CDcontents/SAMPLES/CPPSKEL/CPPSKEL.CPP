/*
 * CppSkel.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 9, Listing 9-1
 *
 * Show how to cast the parameters to _beginthreadex 
 * so that they will work in Visual C++ 4.x with
 * the new stricter type checking.
 *
 * Build this file with the command line:
 *
 *    cl /MD CppSkel.cpp
 *
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(
    LPVOID lpThreadParameter
    );
typedef unsigned *PBEGINTHREADEX_THREADID;

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
    HANDLE hThread;
    DWORD dwThreadId;
    int i = 0;

    hThread = (HANDLE)_beginthreadex(NULL,
            0,
            (PBEGINTHREADEX_THREADFUNC)ThreadFunc,
            (LPVOID)i,
            0,
            (PBEGINTHREADEX_THREADID)&dwThreadId
        );
    if (hThread) {
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
    }
    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
    // Do something ...

    return 0;
}
