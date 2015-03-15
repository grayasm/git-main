/*
 * OutpThrd.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 11. This sample is discussed in
 * the text, but there is no associated listing.
 *
 * Launch a dialog in another thread using both
 * MFC and Win32. Demonstrate the related problems.
 */

#include "stdafx.h"
#include "Cancel.h"
#include "OutpThrd.h"
#include "OutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputCancelDlgThread

IMPLEMENT_DYNCREATE(COutputCancelDlgThread, CWinThread)

COutputCancelDlgThread::COutputCancelDlgThread()
{
}

COutputCancelDlgThread::~COutputCancelDlgThread()
{
}

BOOL COutputCancelDlgThread::InitInstance()
{
	m_pDlg->Go();

	return TRUE;
}

int COutputCancelDlgThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(COutputCancelDlgThread, CWinThread)
	//{{AFX_MSG_MAP(COutputCancelDlgThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputCancelDlgThread message handlers
