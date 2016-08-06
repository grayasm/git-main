/*
 * Demonstrates worker thread startup in MFC without AfxBeginThread()
 */

#include <afxwin.h>

CWinApp TheApp;

class CUserThread : public CWinThread
{
public:
	CUserThread(AFX_THREADPROC pfnThreadProc);
	static UINT ThreadFunc(LPVOID param);

public:
	int		m_nStartCounter;

protected:
	virtual void Go();
};

CUserThread::CUserThread(AFX_THREADPROC pfnThreadProc)
: CWinThread(pfnThreadProc, NULL) // Undocumented ctor
{
	m_bAutoDelete = FALSE;
	m_pThreadParams = this;
}

// static
UINT CUserThread::ThreadFunc(LPVOID param)
{
	CUserThread* pThread = (CUserThread*) param;
	pThread->Go();
	return 0;
}

void CUserThread::Go()
{
	int n = m_nStartCounter;
	for(int i=0; i < 10; ++i)
		printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
}

int main()
{
	CUserThread* pThreads[5];

	for(int i=0; i < 5; ++i)
	{
		pThreads[i] = new CUserThread( CUserThread::ThreadFunc );
		pThreads[i]->m_nStartCounter = i;
		VERIFY( pThreads[i]->CreateThread() );
		printf("Thread launched %d\n", i);
	}

	for(int i=0; i < 5; ++i)
	{
		WaitForSingleObject(pThreads[i]->m_hThread, INFINITE);
		delete pThreads[i];
	}

	printf("Exit\n\n");

	return 0;
}

