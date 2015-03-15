// BookSet.cpp : implementation of the CAwBooksSet class
//

#include "stdafx.h"
#include "BookSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAwBooksSet implementation

IMPLEMENT_DYNAMIC(CAwBooksSet, CRecordset)

CAwBooksSet::CAwBooksSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAwBooksSet)
	m_Title = _T("");
	m_Category = _T("");
	m_Author = _T("");
	m_Page_Count = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CAwBooksSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Windows Books");
}

CString CAwBooksSet::GetDefaultSQL()
{
	return _T("[Books]");
}

void CAwBooksSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAwBooksSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Category]"), m_Category);
	RFX_Text(pFX, _T("[Author]"), m_Author);
	RFX_Long(pFX, _T("[Page Count]"), m_Page_Count);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAwBooksSet diagnostics

#ifdef _DEBUG
void CAwBooksSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAwBooksSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
