// CdDoc.cpp : implementation of the CCopyDataDoc class
//

#include "stdafx.h"
#include "CopyData.h"

#include "CdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyDataDoc

IMPLEMENT_DYNCREATE(CCopyDataDoc, CDocument)

BEGIN_MESSAGE_MAP(CCopyDataDoc, CDocument)
	//{{AFX_MSG_MAP(CCopyDataDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyDataDoc construction/destruction

CCopyDataDoc::CCopyDataDoc()
{
	// TODO: add one-time construction code here

}

CCopyDataDoc::~CCopyDataDoc()
{
}

BOOL CCopyDataDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCopyDataDoc serialization

void CCopyDataDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CCopyDataDoc diagnostics

#ifdef _DEBUG
void CCopyDataDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCopyDataDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCopyDataDoc commands
