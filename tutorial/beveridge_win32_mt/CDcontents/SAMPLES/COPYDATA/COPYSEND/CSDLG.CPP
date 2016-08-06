/*
 * CsDlg.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 13.
 *
 * Dialog-based application that searches for the CopyRecv
 * window and sends that window commands using WM_COPYDATA.
 */

#include "stdafx.h"
#include "CopySend.h"
#include "CsDlg.h"
#include "MtVerify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const LPCSTR szDisplayAppName = "CopyRecv Display Window";

// Define some action commands that tell the display
// window what to do
enum { ACTION_DISPLAY_TEXT, ACTION_CLEAR_WINDOW };


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
// CCopySendDlg dialog

CCopySendDlg::CCopySendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopySendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopySendDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopySendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopySendDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCopySendDlg, CDialog)
	//{{AFX_MSG_MAP(CCopySendDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopySendDlg message handlers

BOOL CCopySendDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCopySendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCopySendDlg::OnPaint() 
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
HCURSOR CCopySendDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCopySendDlg::OnOk() 
{
    CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SENDTEXT);
    ASSERT_VALID(pEdit);

    // Get the text from the edit control
    CString strDisplayText;
    pEdit->GetWindowText(strDisplayText);

    COPYDATASTRUCT cds;
    memset(&cds, 0, sizeof(cds));
    cds.dwData = ACTION_DISPLAY_TEXT;
    cds.cbData = strDisplayText.GetLength() + 1; // +1 for the NULL
    cds.lpData = (LPVOID)(LPCTSTR) strDisplayText;

    SendToServer(cds);
}


void CCopySendDlg::OnClear() 
{
    COPYDATASTRUCT cds;
    memset(&cds, 0, sizeof(cds));
    cds.dwData = ACTION_CLEAR_WINDOW;

    SendToServer(cds);
}

void CCopySendDlg::SendToServer(const COPYDATASTRUCT& cds)
{
    CWnd *pDisplayWnd = CWnd::FindWindow(NULL, szDisplayAppName);
    if (pDisplayWnd)
    {
        pDisplayWnd->SendMessage(WM_COPYDATA,
            (WPARAM)GetSafeHwnd(), (LPARAM)&cds);
    }
    else
        AfxMessageBox(IDS_ERR_NOSERVER);
}

void CCopySendDlg::OnExit() 
{
    EndDialog(IDOK);	
}
