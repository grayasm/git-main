// CdView.cpp : implementation of the CCopyDataView class
//

#include "stdafx.h"
#include "CopyData.h"

#include "CdDoc.h"
#include "CdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyDataView

IMPLEMENT_DYNCREATE(CCopyDataView, CEditView)

BEGIN_MESSAGE_MAP(CCopyDataView, CEditView)
	//{{AFX_MSG_MAP(CCopyDataView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyDataView construction/destruction

CCopyDataView::CCopyDataView()
{
	// TODO: add construction code here

}

CCopyDataView::~CCopyDataView()
{
}

BOOL CCopyDataView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	cs.style |= ES_READONLY|ES_MULTILINE;

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CCopyDataView drawing

void CCopyDataView::OnDraw(CDC* pDC)
{
	CCopyDataDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCopyDataView diagnostics

#ifdef _DEBUG
void CCopyDataView::AssertValid() const
{
	CEditView::AssertValid();
}

void CCopyDataView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CCopyDataDoc* CCopyDataView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCopyDataDoc)));
	return (CCopyDataDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCopyDataView message handlers

