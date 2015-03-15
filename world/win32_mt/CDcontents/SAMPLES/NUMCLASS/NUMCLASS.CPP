/*
 * NumClass.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 10, Listing 10-3
 *
 * Demonstrate worker thread startup in MFC
 * without AfxBeginThread.
 *
 * Compile with the IDE or: nmake -f NumClass.mak
 */

#include <afxwin.h>

CWinApp TheApp;


class CUserThread : public CWinThread
{
public:  // Member functions
    CUserThread(AFX_THREADPROC pfnThreadProc);

    static UINT ThreadFunc(LPVOID param);

public:  // Member data
    int m_nStartCounter;

private: // The "real" startup function
    virtual void Go();
};

CUserThread::CUserThread(AFX_THREADPROC pfnThreadProc)
 : CWinThread(pfnThreadProc, NULL)  // Undocumented constructor
{
    m_bAutoDelete = FALSE;

    // Set the pointer to the class to be the startup value.
    // m_pThreadParams is undocumented,
    // but there is no work-around.
    m_pThreadParams = this;
}


int main()
{
    CUserThread* pThreads[5];

    for (int i=0; i<5; i++)
    {
        // Pass our static member as the startup function
        pThreads[i] = new CUserThread( CUserThread::ThreadFunc );

        // Set the appropriate member variable
        pThreads[i]->m_nStartCounter = i;

        // Start the thread in motion
        VERIFY(
          pThreads[i]->CreateThread() );
        printf("Thread launched %d\n", i);
    }

    for (i=0; i<5; i++)
    {
        WaitForSingleObject(pThreads[i]->m_hThread, INFINITE);
        delete pThreads[i];
    }

    return 0;
}


// static
UINT CUserThread::ThreadFunc(LPVOID n)
{
    CUserThread* pThread = (CUserThread*)n;
    pThread->Go();
    return 0;
}

void CUserThread::Go()
{
    int n = m_nStartCounter;
    for (int i=0;i<10;i++)
        printf("%d%d%d%d%d%d%d%d\n",n,n,n,n,n,n,n,n);
}
