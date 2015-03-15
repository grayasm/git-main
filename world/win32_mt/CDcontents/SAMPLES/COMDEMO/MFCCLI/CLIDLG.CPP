/*
 * CliDlg.cpp : implementation file
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 17
 *
 * Communicates to a FreeThreaded COM Object
 */

#include "stdafx.h"
#include "MfcCli.h"
#include "CliDlg.h"

//
// Include the interface definition from the ComDemo.DLL
//
#define IID_DEFINED
#include "..\ComDemo_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcCliDlg dialog

// Registered Window Messages for notifying when threads are done.
UINT g_msgSlowThreadDone = RegisterWindowMessage("SlowThreadDone");
UINT g_msgFastThreadDone = RegisterWindowMessage("FastThreadDone");

CMfcCliDlg::CMfcCliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcCliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMfcCliDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoIncr = NULL;
	m_iSlowThreadCount = 0;
	m_iFastThreadCount = 0;
}

void CMfcCliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcCliDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMfcCliDlg, CDialog)
	//{{AFX_MSG_MAP(CMfcCliDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BK_FAST, OnBkFast)
	ON_BN_CLICKED(IDC_BK_SLOW, OnBkSlow)
	ON_BN_CLICKED(IDC_UI_FAST, OnUiFast)
	ON_BN_CLICKED(IDC_UI_SLOW, OnUiSlow)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_WM_CLOSE()
	ON_REGISTERED_MESSAGE(g_msgSlowThreadDone, OnSlowThreadDone)
	ON_REGISTERED_MESSAGE(g_msgFastThreadDone, OnFastThreadDone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcCliDlg message handlers

BOOL CMfcCliDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//
	// Create the CLSID_CAutoIncr COM object
	//
	m_pAutoIncr = CreateAutoIncr();
	if (!m_pAutoIncr)
	{
		TRACE(_T("Failed to create m_pAutoIncr!\n"));
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMfcCliDlg::OnClose() 
{	//
	// Release the COM object created in OnInitDialog()
	//
	if (m_pAutoIncr)
		m_pAutoIncr->Release();
	
	CDialog::OnClose();
}

void CMfcCliDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMfcCliDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMfcCliDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//
// Bring up the About Dialog Box when the button is pressed.
//
void CMfcCliDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}


//
// This function will create a CLSID_CAutoIncr COM object and return 
// an IAutoIncr interface to the object
// 
IAutoIncr* CMfcCliDlg::CreateAutoIncr() 
{
	// Create the object and get a IUnknown* to the object
	TRACE(_T("\nSTARTING\n=============================\n"));
	TRACE(_T("Calling CoCreateInstance()...\n"));
	IUnknown* pUnk = NULL;
	HRESULT hRes = CoCreateInstance(CLSID_CAutoIncr, NULL, CLSCTX_ALL,
		IID_IUnknown, (void**)&pUnk);
	if (FAILED(hRes))
	{
		TRACE(_T("Failed to create CLSID_CAutoIncr\n"));
		return NULL;
	}
	TRACE(_T("Object created\n"));

	// Use QueryInterface() to get the IAutoIncr interface
	IAutoIncr* pCom = NULL;
	hRes = pUnk->QueryInterface(IID_IAutoIncr, (LPVOID*)&pCom);
	pUnk->Release();
	if (FAILED(hRes))
	{
		TRACE(_T("QueryInterface() for IID_IAutoIncr failed\n"));
		return NULL;
	}

	return pCom;
}

void CMfcCliDlg::OnUiFast() 
{	// Get the FastCounter property in the UI thread
	// Shows an hourglass since no other user input is allowed until we finish

	CWaitCursor wait;	// Show an hourglass

	if (m_pAutoIncr)
	{
		WORD value;
		m_pAutoIncr->get_FastCounter(&value);
		SetDlgItemInt(IDC_EDIT_FAST_COUNTER, value);
	}	// end if
}

void CMfcCliDlg::OnUiSlow() 
{	// Get the SlowCounter property in the UI thread
	// Shows an hourglass since no other user input is allowed until we finish

	CWaitCursor wait;	// Show an hourglass

	if (m_pAutoIncr)
	{
		WORD value;
		m_pAutoIncr->get_SlowCounter(&value);
		SetDlgItemInt(IDC_EDIT_SLOW_COUNTER, value);
	}	// end if
}

UINT CMfcCliDlg::FastCounterThreadFunc( LPVOID pParam )
{	// Thread Functions for background thread that will get FastCounter
	CThreadInfo* pInfo = (CThreadInfo*) pParam;

	// Initializes the thread for multi-threaded object concurrency
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (pInfo->m_pAutoIncr)
	{
		// Get Property Value of COM Object
		WORD value;
		pInfo->m_pAutoIncr->get_FastCounter(&value);

		// Show value in specified control window
		CString szText; szText.Format("%d", value);
		::SendMessage(pInfo->m_hwndCtrl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) szText);

		// Tell Dialog that thread is done
		::SendMessage(pInfo->m_hwndDlg, g_msgFastThreadDone, 0, 0);
	}	// end if

	// Free data structure passed to this thread
	if (pInfo)
		delete pInfo;

	return 0;
}

UINT CMfcCliDlg::SlowCounterThreadFunc( LPVOID pParam )
{	// Thread Functions for background thread that will get SlowCounter
	CThreadInfo* pInfo = (CThreadInfo*) pParam;

	// Initializes the thread for multi-threaded object concurrency
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (pInfo->m_pAutoIncr)
	{
		// Get Property Value of COM Object
		WORD value;
		pInfo->m_pAutoIncr->get_SlowCounter(&value);

		// Show value in specified control window
		CString szText; szText.Format("%d", value);
		::SendMessage(pInfo->m_hwndCtrl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) szText);

		// Tell Dialog that thread is done
		::SendMessage(pInfo->m_hwndDlg, g_msgSlowThreadDone, 0, 0);
	}	// end if

	// Free data structure passed to this thread
	if (pInfo)
		delete pInfo;

	return 0;
}

void CMfcCliDlg::OnBkFast() 
{	// Get the FastCounter property in a background worker thread
	// User can still do anything with the UI!
	CThreadInfo* pInfo = new CThreadInfo(m_pAutoIncr, 
		GetSafeHwnd(), 
		GetDlgItem(IDC_EDIT_FAST_COUNTER)->GetSafeHwnd());

	if (AfxBeginThread(&CMfcCliDlg::FastCounterThreadFunc, (LPVOID) pInfo))
	{	// Thread created successfully, so update count
		m_iFastThreadCount++;
		SetDlgItemInt(IDC_EDIT_FAST_THREADS, m_iFastThreadCount);
	}	// end if
}

void CMfcCliDlg::OnBkSlow() 
{	// Get the SlowCounter property in a background worker thread
	// User can still do anything with the UI!
	CThreadInfo* pInfo = new CThreadInfo(m_pAutoIncr, 
		GetSafeHwnd(), 
		GetDlgItem(IDC_EDIT_SLOW_COUNTER)->GetSafeHwnd());

	if (AfxBeginThread(&CMfcCliDlg::SlowCounterThreadFunc, (LPVOID) pInfo))
	{	// Thread created successfully, so update count
		m_iSlowThreadCount++;
		SetDlgItemInt(IDC_EDIT_SLOW_THREADS, m_iSlowThreadCount);
	}	// end if
}


LRESULT CMfcCliDlg::OnFastThreadDone(WPARAM wParam, LPARAM lParam)
{	// A Fast background thread has finished, so update count
	m_iFastThreadCount--;
	SetDlgItemInt(IDC_EDIT_FAST_THREADS, m_iFastThreadCount);
	return 0;
}

LRESULT CMfcCliDlg::OnSlowThreadDone(WPARAM wParam, LPARAM lParam)
{	// A Slow background thread has finished, so update count
	m_iSlowThreadCount--;
	SetDlgItemInt(IDC_EDIT_SLOW_THREADS, m_iSlowThreadCount);
	return 0;
}
