// CancelView.h : interface of the CCancelView class
//
/////////////////////////////////////////////////////////////////////////////

class CCancelView : public CView
{
protected: // create from serialization only
	CCancelView();
	DECLARE_DYNCREATE(CCancelView)

// Attributes
public:
	CCancelDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCancelView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCancelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void LaunchHelper(HWND hParent);

// Generated message map functions
protected:
	//{{AFX_MSG(CCancelView)
	afx_msg void OnLaunch();
	afx_msg void OnBoom();
	afx_msg void OnLaunchWin32();
	afx_msg void OnViewTightLoop();
	afx_msg void OnViewNoparent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CancelView.cpp
inline CCancelDoc* CCancelView::GetDocument()
   { return (CCancelDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
