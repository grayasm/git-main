/*
 * Numbers.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 10, Listing 10-1
 *
 * Demonstrate basic thread startup in MFC
 * using AfxBeginThread.
 *
 * Compile with the IDE or: nmake -f numbers.mak
 */

#include <afxwin.h>

CWinApp TheApp;

UINT ThreadFunc(LPVOID);

int main()
{
    for (int i=0; i<5; i++)
    {
        if (AfxBeginThread( ThreadFunc, (LPVOID)i ))
            printf("Thread launched %d\n", i);
    }

    // Wait for the threads to complete.
    Sleep(2000);

    return 0;
}


UINT ThreadFunc(LPVOID n)
{
    for (int i=0;i<10;i++)
	    printf("%d%d%d%d%d%d%d%d\n",n,n,n,n,n,n,n,n);
    return 0;
}
