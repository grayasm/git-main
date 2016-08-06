/*
 * MfcCli.h : main header file for the MFCCLI application
 *
 * Sample code for "Multitasking in Win32"
 * This is from Chapter 16???
 *
 * Communicates to a FreeThreaded COM Object
 */

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcCliApp:
// See MfcCli.cpp for the implementation of this class
//

class CMfcCliApp : public CWinApp
{
public:
	CMfcCliApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcCliApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfcCliApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
