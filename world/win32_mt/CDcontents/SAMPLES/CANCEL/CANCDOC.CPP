/*
 * CancDoc.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 11. This sample is discussed in
 * the text, but there is no associated listing.
 */

#include "stdafx.h"
#include "Cancel.h"

#include "CancDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCancelDoc

IMPLEMENT_DYNCREATE(CCancelDoc, CDocument)

BEGIN_MESSAGE_MAP(CCancelDoc, CDocument)
	//{{AFX_MSG_MAP(CCancelDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCancelDoc construction/destruction

CCancelDoc::CCancelDoc()
{
	// TODO: add one-time construction code here

}

CCancelDoc::~CCancelDoc()
{
}

BOOL CCancelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCancelDoc serialization

void CCancelDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCancelDoc diagnostics

#ifdef _DEBUG
void CCancelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCancelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCancelDoc commands
