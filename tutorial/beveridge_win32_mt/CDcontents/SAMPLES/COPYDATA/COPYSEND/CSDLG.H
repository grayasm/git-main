// CsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCopySendDlg dialog

class CCopySendDlg : public CDialog
{
// Construction
public:
	CCopySendDlg(CWnd* pParent = NULL);	// standard constructor

	void SendToServer(const COPYDATASTRUCT& pcds);

// Dialog Data
	//{{AFX_DATA(CCopySendDlg)
	enum { IDD = IDD_COPYSEND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopySendDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCopySendDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOk();
	afx_msg void OnExit();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
