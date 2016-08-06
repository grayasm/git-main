/*
 * Member.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 9, Listing 9-3
 *
 * Shows how to start a thread based on a
 * class member function using a static
 * member function.
 *
 * Build this file with the command line:
 *
 *    cl /MD Member.cpp
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

//
// This ThreadObject is created by a thread
// that wants to start another thread. All
// public member functions except ThreadFunc()
// are called by that original thread. The
// virtual function ThreadMemberFunc() is
// the start of the new thread.
//
class ThreadObject
{
public:
    ThreadObject();
    void StartThread();
    void WaitForExit();

    static DWORD WINAPI ThreadFunc(LPVOID param);

protected:
    virtual DWORD ThreadMemberFunc();

    HANDLE  m_hThread;
    DWORD   m_ThreadId;
};

ThreadObject::ThreadObject()
{
    m_hThread = NULL;
    m_ThreadId = 0;
}

void ThreadObject::StartThread()
{
    m_hThread = (HANDLE)_beginthreadex(NULL,
        0,
        (PBEGINTHREADEX_THREADFUNC) ThreadObject::ThreadFunc,
        (LPVOID)this,
        0,
        (PBEGINTHREADEX_THREADID) &m_ThreadId );
    if (m_hThread) {
        printf("Thread launched\n");
    }
}

void ThreadObject::WaitForExit()
{
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
}

//
// This is a static member function.  Unlike
// C static functions, you only place the static
// declaration on the function declaration in the
// class, not on its implementation.
//
// Static member functions have no "this" pointer,
// but do have access rights.
//
DWORD WINAPI ThreadObject::ThreadFunc(LPVOID param)
{
    // Use the param as the address of the object
    ThreadObject* pto = (ThreadObject*)param;
    // Call the member function. Since we have a
    // proper object pointer, even virtual functions
    // will be called properly.
    return pto->ThreadMemberFunc();
}


//
// This above function ThreadObject::ThreadFunc()
// calls this function after the thread starts up.
//
DWORD ThreadObject::ThreadMemberFunc()
{
    // Do something useful ...
    return 0;
}


void main()
{
    ThreadObject obj;

    obj.StartThread();
    obj.WaitForExit();
}
