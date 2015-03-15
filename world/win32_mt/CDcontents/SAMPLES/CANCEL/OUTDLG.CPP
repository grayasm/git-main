/*
 * OutDlg.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 11. This sample is discussed in
 * the text, but there is no associated listing.
 *
 * Launch a dialog in another thread using both
 * MFC and Win32. Demonstrate the related problems.
 */

//////////////////////////////////////////////////////////////////////////
// INCLUDE FILES

#include "stdafx.h"
#include "Cancel.h"
#include "MainFrm.h"
#include "OutpThrd.h"
#include "OutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CLASS DEFINITIONS

BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
   ON_MESSAGE(WM_USER_PREPARE_TO_CLOSE, OnPrepareToClose)
END_MESSAGE_MAP()


/*
 * Default constructor for the dialog.
 *
 * Set no thread
 *
 * The param "n" is the index into
 * the handle array, kept for informational
 * purposes.
 */
CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pThread = NULL;

	Initialize();
}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	//}}AFX_DATA_MAP
}


/******************************************************************************
 *
 *	CProgressDlg::OnCancel
 *
 * If the user presses the cancel button, set the cancel flag.
 * Although not implemented, the dialog would normally be closed
 * by the primary thread after it notices that the flag is set.
 */                                                              
void CProgressDlg::OnCancel()
{
	// DI Comment: Don't call base class CDialog::OnCancel(), because it calls EndDialog(),
	// which will make dialog box invisible but will not destroy it.
	// !!! Don't call DestroyWindow() here, it is to early.

	int ulResult = AfxMessageBox(IDS_ERR_OUTPUT_CANCEL, MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 );

	if( ulResult == IDYES )
		m_fIsCancelled = TRUE;
}


/******************************************************************************
 *
 *	CProgressDlg::OnInitDialog
 *
 * Center the dialog in the middle of the mainframe.
 */                                                              
BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// This call generates msgs to the mainframe that will
	// never be answered. However,  if you take this call
	// out the program still does not work (as shown in Win32)
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/******************************************************************************
 *
 *	CProgressDlg::OnInitDialog
 *
 * Initialize members.
 */                                                              
void CProgressDlg::Initialize()
{
	m_fIsCancelled = FALSE;
} 


/******************************************************************************
 *
 *	CProgressDlg::StartDialog
 *
 * Start the thread that will run the dialog.
 */                                                              
BOOL	CProgressDlg::StartDialog()
{
    // Dialog never exited and/or thread never died
	ASSERT(m_pThread==NULL);
	
	m_pThread = (COutputCancelDlgThread*)AfxBeginThread(
						RUNTIME_CLASS(COutputCancelDlgThread),
						THREAD_PRIORITY_ABOVE_NORMAL,	// Keep it responsive
						0,
						CREATE_SUSPENDED
					);

	// We created the thread suspended so we could
	// pass m_pDlg here.
	if (m_pThread)
	{
		m_pThread->m_pDlg = this;
		m_pThread->ResumeThread();
	}

	return m_pThread != NULL;
}


/******************************************************************************
 *
 *	CProgressDlg::StartDialog
 *
 * Gracefully shut down the dialog across the thread boundaries.
 */                                                              
void	CProgressDlg::CloseDialog()
{
	if (m_pThread == NULL)
        return;

	SendMessage(WM_USER_PREPARE_TO_CLOSE);
	// The dialog thread has higher priority, so it will run to
	// completion before this thread gets control again.
	m_pThread = NULL;
}


/******************************************************************************
 *
 *	CProgressDlg::StartDialog
 *
 * Creates and initializes the dialog. This runs in the second thread.
 * Should only be called during InitInstance of the thread for this dlg.
 */                                                              
BOOL	CProgressDlg::Go()
{
	// Initializes modeless dialog
	Initialize();

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd( );

	// If you get rid of the CenterWindow call in OnInitDialog
	// and change this pMainFrame to NULL, then the window
	// comes up but does not behave properly.
	if( !Create( IDD_OUTPUT_MSGDLG, pMainFrame ))
		return FALSE;

	return TRUE;
}


/*****************************************************************************
 *
 *	CProgressDlg::OnPrepareToClose
 *
 * Shut down the dialog and the thread. This function
 * should not be called directly. Instead, send the
 * thread a WM_USER_PREPARE_TO_CLOSE.
 */

LRESULT CProgressDlg::OnPrepareToClose(WPARAM, LPARAM)
{
	DestroyWindow();
	::PostQuitMessage(0);
	return TRUE;
}
