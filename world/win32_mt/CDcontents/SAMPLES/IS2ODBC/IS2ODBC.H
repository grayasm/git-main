// IS2ODBC.H - Header file for your Internet Server
//    ISAPI to ODBC Extension

#include "resource.h"

class CIs2OdbcExtension : public CHttpServer
{
public:
	CIs2OdbcExtension();
	~CIs2OdbcExtension();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CIs2OdbcExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	virtual BOOL InitInstance(CHttpServerContext* pCtxt);
  	//}}AFX_VIRTUAL

	// TODO: Add handlers for your commands here.
	// For example:

	//
	// Added optional Filter and Sort arguments
	//
	void Default(CHttpServerContext* pCtxt, LPTSTR pszFilter="~", LPTSTR pszSort="~");

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CIs2OdbcExtension)
	//}}AFX_MSG
};

