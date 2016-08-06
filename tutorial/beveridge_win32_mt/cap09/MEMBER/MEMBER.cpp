/*
 * Member.cpp
 *
 * Shows how to start a thread based on a class member function using either a static
 * member function or a C-style function.
 */

#include <windows.h>
#include <stdio.h>
#include <process.h>

typedef unsigned (WINAPI *pTHREADFUNC)(LPVOID);
typedef unsigned *pTHREADID;

class ThreadObject
{
public:
	ThreadObject();
	void StartThread();
	static DWORD WINAPI ThreadFunc(LPVOID);
	void WaitForExit();

protected:
	virtual DWORD ThreadMemberFunc();

	HANDLE	m_hThread;
	DWORD	m_threadId;
};

ThreadObject::ThreadObject()
{
	m_hThread = NULL;
	m_threadId = 0;
	printf("\n\t%s", __FUNCTION__);
}

void ThreadObject::StartThread()
{
	m_hThread = (HANDLE) _beginthreadex(
							NULL,
							0,
							(pTHREADFUNC) ThreadFunc,
							(LPVOID) this,
							0,
							(pTHREADID) &m_threadId);

	if(m_hThread)
		printf("\n\t%s", __FUNCTION__);
}

void ThreadObject::WaitForExit()
{
	printf("\n\t%s", __FUNCTION__);
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
}

/*
	This is a static member function. Unlike C static functions, you only place the
	static declaration on the function declaration in the class, not on its implementation.

	Static member functions have no "this" pointer, but do have access rights.
 */
DWORD WINAPI ThreadObject::ThreadFunc(LPVOID param)
{
	printf("\n\t%s", __FUNCTION__);
	ThreadObject* pto = (ThreadObject*)param;
	return pto->ThreadMemberFunc();
}

DWORD ThreadObject::ThreadMemberFunc()
{
	printf("\n\t%s", __FUNCTION__);
	printf("\n\tWait 1 sec");
	Sleep(1000);
	printf("\n\tThread idle");
	return 0;
}

void main()
{
	ThreadObject obj;

	obj.StartThread();
	obj.WaitForExit();

	printf("\n\n");
}