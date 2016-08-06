/*
 * Entry.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 14, Listing 14-1
 *
 * Demonstrate a very simple DLL that prints
 * status messages when its functions are called
 * a provides a single entry point called
 * TheFunction() for test purposes.
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
     DWORD tid = GetCurrentThreadId();

     // Why are we being called?
    switch( fdwReason )  
    { 
        case DLL_PROCESS_ATTACH:
            printf("DLL:\tProcess attach (tid = %d)\n", tid);
            break;

        case DLL_THREAD_ATTACH:
            printf("DLL:\tThread attach (tid = %d)\n", tid);
            break;

        case DLL_THREAD_DETACH:
            printf("DLL:\tThread detach (tid = %d)\n", tid);
            break;

        case DLL_PROCESS_DETACH:
            printf("DLL:\tProcess detach (tid = %d)\n", tid);
            break;
    }
    return TRUE;
}

_declspec( dllexport ) BOOL TheFunction()
{
    printf("DLL:\tTheFunction() called\n");
    return TRUE;
}
