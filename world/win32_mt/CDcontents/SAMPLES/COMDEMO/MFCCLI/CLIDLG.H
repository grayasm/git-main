/*
 * CliDlg.h : header file
 *
 * Sample code for "Multitasking in Win32"
 * This is from Chapter 16???
 *
 * Defines Dialog Class for communicating with
 * FreeThreaded COM Object
 */

/////////////////////////////////////////////////////////////////////////////
// CMfcCliDlg dialog

class CMfcCliDlg : public CDialog
{
// Construction
public:
	CMfcCliDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMfcCliDlg)
	enum { IDD = IDD_MFCCLI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcCliDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Remember a pointer to the COM object we will be using
	IAutoIncr* m_pAutoIncr;
	IAutoIncr* CreateAutoIncr(void);

	// Keep track of the number of background threads that have been created
	WORD m_iSlowThreadCount;
	WORD m_iFastThreadCount;

	// Message sent by background thread to dialog box when finished
	afx_msg LONG OnSlowThreadDone(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnFastThreadDone(WPARAM wParam, LPARAM lParam);

	// Declare Thread Functions for background threads that will access the COM object
	// Use static declarations since these are C functions
	static UINT FastCounterThreadFunc( LPVOID pParam );
	static UINT SlowCounterThreadFunc( LPVOID pParam );

	// Generated message map functions
	//{{AFX_MSG(CMfcCliDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBkFast();
	afx_msg void OnBkSlow();
	afx_msg void OnUiFast();
	afx_msg void OnUiSlow();
	afx_msg void OnAbout();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CThreadInfo

class CThreadInfo
{	// This holds information passed to the background threads by the UI
public:
	CThreadInfo(IAutoIncr* pAutoIncr, HWND hwndDlg, HWND hwndCtrl) 
		: m_pAutoIncr(pAutoIncr), m_hwndDlg(hwndDlg), m_hwndCtrl(hwndCtrl)
	{};

	IAutoIncr* m_pAutoIncr;
	HWND m_hwndDlg;
	HWND m_hwndCtrl;
};


