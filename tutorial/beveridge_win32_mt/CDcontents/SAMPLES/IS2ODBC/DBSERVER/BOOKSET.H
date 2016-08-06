// BookSet.h : interface of the CAwBooksSet class
//
/////////////////////////////////////////////////////////////////////////////

class CAwBooksSet : public CRecordset
{
public:
	CAwBooksSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAwBooksSet)

// Field/Param Data
	//{{AFX_FIELD(CAwBooksSet, CRecordset)
	CString	m_Title;
	CString	m_Category;
	CString	m_Author;
	long	m_Page_Count;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwBooksSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};
