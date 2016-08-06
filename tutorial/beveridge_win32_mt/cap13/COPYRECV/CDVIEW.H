// CdView.h : interface of the CCopyDataView class
//
/////////////////////////////////////////////////////////////////////////////

class CCopyDataView : public CEditView
{
protected: // create from serialization only
	CCopyDataView();
	DECLARE_DYNCREATE(CCopyDataView)

// Attributes
public:
	CCopyDataDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyDataView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCopyDataView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCopyDataView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CdView.cpp
inline CCopyDataDoc* CCopyDataView::GetDocument()
   { return (CCopyDataDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
