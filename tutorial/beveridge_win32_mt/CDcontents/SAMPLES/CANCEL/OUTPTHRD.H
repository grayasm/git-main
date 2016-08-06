// OutpThrd.h : header file
//

class CProgressDlg;

/////////////////////////////////////////////////////////////////////////////
// COutputCancelDlgThread thread

class COutputCancelDlgThread : public CWinThread
{
	DECLARE_DYNCREATE(COutputCancelDlgThread)

public:
	COutputCancelDlgThread();           // protected constructor used by dynamic creation
	virtual ~COutputCancelDlgThread();

// Attributes
public:

	CProgressDlg* m_pDlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputCancelDlgThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutputCancelDlgThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
