// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CopyData.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Define the action commands
enum { ACTION_DISPLAY_TEXT, ACTION_CLEAR_WINDOW };

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_COPYDATA, OnCopyData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style &= ~(FWS_ADDTOTITLE);	// Do not put in a document name

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

LONG CMainFrame::OnCopyData( UINT wParam, LONG lParam)
{
//  HWND hwnd = (HWND)wParam;            // handle of sending window 
    PCOPYDATASTRUCT pcds = (PCOPYDATASTRUCT) lParam;

    // The view is inside the mainframe,
    //and the edit control is in the view
    CEditView* pView = (CEditView*)GetActiveView();
    ASSERT_VALID(pView);

    // Find the edit control
    CEdit& ctlEdit = pView->GetEditCtrl();

    switch (pcds->dwData)
    {
    case ACTION_DISPLAY_TEXT:
        {
        LPCSTR szNewString = (LPCSTR)(pcds->lpData);
        // Setting a CString equal to a LPCSTR makes a copy of the string.
        CString strTextToDisplay = szNewString;
        // Throw away any \r\n that may already be there
        strTextToDisplay.TrimRight();
        // Now add our own
        strTextToDisplay += "\r\n";

        // Set the cursor back at the end of the text
        int nEditLen = ctlEdit.GetWindowTextLength();
        ctlEdit.SetSel(nEditLen, nEditLen);
        // Append the text
        ctlEdit.ReplaceSel(strTextToDisplay);
        ctlEdit.ShowCaret();
        break;
        }

    case ACTION_CLEAR_WINDOW:
        ctlEdit.SetWindowText("");
        break;

    default:
        break;
    }

    return 1;
}
