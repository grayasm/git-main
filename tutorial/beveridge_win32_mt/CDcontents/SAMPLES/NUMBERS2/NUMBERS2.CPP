/*
 * Numbers2.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 10, Listing 10-2
 *
 * Demonstrate thread startup in MFC
 * using AfxBeginThread, but prevent
 * CWinThread from auto-deletion so that
 * we can wait on the thread.
 *
 * Compile with the IDE or: nmake -f numbers2.mak
 */

#include <afxwin.h>

CWinApp TheApp;

UINT ThreadFunc(LPVOID);

int main()
{
    CWinThread* pThreads[5];

    for (int i=0; i<5; i++)
    {
        pThreads[i] = AfxBeginThread(
                        ThreadFunc,
                        (LPVOID)i,
                        THREAD_PRIORITY_NORMAL,
                        0,
                        CREATE_SUSPENDED
                      );
        ASSERT(pThreads[i]);
        pThreads[i]->m_bAutoDelete = FALSE;
        pThreads[i]->ResumeThread();
        printf("Thread launched %d\n", i);
    }
   
    for (i=0; i<5; i++)
    {
        WaitForSingleObject(pThreads[i]->m_hThread, INFINITE);
        delete pThreads[i];
    }

    return 0;
}


UINT ThreadFunc(LPVOID n)
{
    for (int i=0;i<10;i++)
	    printf("%d%d%d%d%d%d%d%d\n",n,n,n,n,n,n,n,n);
    return 0;
}
