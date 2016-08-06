// ShareMem.h : main header file for the SHAREMEM application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// SharedBlock
//

struct SharedBlock;

extern SharedBlock* gpSharedBlock;
extern HANDLE       ghDataLock;

struct SharedBlock
{
    short   m_nStringCount;
    char __based( gpSharedBlock ) *m_pStrings[1];
};



/////////////////////////////////////////////////////////////////////////////
// CShareMemApp:
// See ShareMem.cpp for the implementation of this class
//

class CShareMemApp : public CWinApp
{
public:
	CShareMemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareMemApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShareMemApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
