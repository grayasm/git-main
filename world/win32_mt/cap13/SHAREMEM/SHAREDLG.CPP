// ShareDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShareMem.h"
#include "ShareDlg.h"

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
// CShareMemDlg dialog

CShareMemDlg::CShareMemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShareMemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShareMemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShareMemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareMemDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShareMemDlg, CDialog)
	//{{AFX_MSG_MAP(CShareMemDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ, OnRead)
	ON_BN_CLICKED(IDC_WRITE, OnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareMemDlg message handlers

BOOL CShareMemDlg::OnInitDialog()
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

void CShareMemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShareMemDlg::OnPaint() 
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
HCURSOR CShareMemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShareMemDlg::OnRead() 
{
    // Make sure the shared memory is available
    ::WaitForSingleObject(ghDataLock, INFINITE);

    CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT);
    ASSERT_VALID(pEdit);
    pEdit->SetWindowText("");
    pEdit->SetSel(-1, -1);
    pEdit->ShowCaret();

    for (int i=0; i<gpSharedBlock->m_nStringCount; i++)
    {
        CString str = gpSharedBlock->m_pStrings[i];
        str += "\r\n";
        pEdit->ReplaceSel(str);
    }

    ::ReleaseMutex(ghDataLock);
}

void CShareMemDlg::OnWrite() 
{
    // Make sure the shared memory is available
    ::WaitForSingleObject(ghDataLock, INFINITE);

    CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT);
    ASSERT_VALID(pEdit);

    int iLineCount = pEdit->GetLineCount();
    gpSharedBlock->m_nStringCount = iLineCount;
    char *pTextBuffer =
        (char *)gpSharedBlock
        + sizeof(SharedBlock)
        + sizeof(char __based(gpSharedBlock) *) * (iLineCount-1);

    char szLineBuffer[256];
    while (iLineCount--)
    {
        // Get the next line from the edit control
        pEdit->GetLine(iLineCount, szLineBuffer, sizeof(szLineBuffer));

        // Terminate it
        szLineBuffer[pEdit->LineLength(pEdit->LineIndex(iLineCount))] = '\0';

        // Store the line in shared memory. The compiler
        // silently translates from a based pointer to
        // a regular pointer, so strcpy() works properly.
        strcpy(pTextBuffer, szLineBuffer);

        // Remember where we put it. Convert to a based
        // ptr before storing the ptr.
        gpSharedBlock->m_pStrings[iLineCount] =
            (char _based(gpSharedBlock) *)pTextBuffer;

        // Skip to the next open space in the buffer
        pTextBuffer += strlen(szLineBuffer) + 1;
    }

    ::ReleaseMutex(ghDataLock);
}
