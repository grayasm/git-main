/*
 * Is2odbc.cpp : Implementation file for Internet Server Extension
 * 		 ISAPI to ODBC Extension
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 16
 *
 * Implement an ISAPI extension that will launch and then
 * talk to an external process that is running the JET engine.
 *
 * The error messages returned by this filter are appropriate
 * for developers. They would need to be changed if this page
 * were being used by endusers.
 */

#include "stdafx.h"
#include "Is2Odbc.h"

// Add our include files here
#include "MtVerify.h"
#include "Request.h"

//
// Define how long an ISAPI thread should wait while 
// handling a DB request.
//
#define TIMEOUT_MUTEX   5000   /* 10 sec wait to do a request */
#define TIMEOUT_EVENT   360000   /* 60 sec wait for results     */

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

CWinApp theApp;

//
// Setup a security descriptor that allows world access
//
SECURITY_DESCRIPTOR sd;
SECURITY_ATTRIBUTES sa;

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CIs2OdbcExtension, CHttpServer)
    // TODO: insert your ON_PARSE_COMMAND() and 
    // ON_PARSE_COMMAND_PARAMS() here to hook up your commands.
    // For example:

    //
    // Added Optional Filter and Sort arguments
    //
    ON_PARSE_COMMAND(Default, CIs2OdbcExtension, ITS_PSTR ITS_PSTR)
    ON_PARSE_COMMAND_PARAMS("Filter=~ Sort=~")
    DEFAULT_PARSE_COMMAND(Default, CIs2OdbcExtension)
END_PARSE_MAP(CIs2OdbcExtension)


///////////////////////////////////////////////////////////////////////
// The one and only CIs2OdbcExtension object

CIs2OdbcExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CIs2OdbcExtension implementation

CIs2OdbcExtension::CIs2OdbcExtension()
{
}

CIs2OdbcExtension::~CIs2OdbcExtension()
{
}

BOOL CIs2OdbcExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
    // Call default implementation for initialization
    CHttpServer::GetExtensionVersion(pVer);

    // Load description string
    TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
    ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
            IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
    _tcscpy(pVer->lpszExtensionDesc, sz);
    return TRUE;
}

BOOL CIs2OdbcExtension::InitInstance(CHttpServerContext* pCtxt)
{
	// Let the base class do its job.
	CHttpServer::InitInstance(pCtxt);

    // create a security descriptor that allows anyone
    //  to get at the event...
    //
    if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
		return FALSE;

    // add a NULL disc. ACL to the security descriptor.
    //
    if (!SetSecurityDescriptorDacl(&sd, TRUE, (PACL) NULL, FALSE))
		return FALSE;

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = &sd;
    sa.bInheritHandle = FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// CIs2OdbcExtension command handlers

//
// Added Filter and Sort arguments
void CIs2OdbcExtension::Default(CHttpServerContext* pCtxt, LPTSTR pszFilter, LPTSTR pszSort)
{
    StartContent(pCtxt);
    WriteTitle(pCtxt);

	CEvent serverRunning(FALSE, TRUE, EVENT_SERVER_RUNNING, &sa);
	if (::GetLastError() != ERROR_ALREADY_EXISTS)
	{
		CString strDllPath;
		GetModuleFileName( theApp.m_hInstance,
							strDllPath.GetBuffer(MAX_PATH),
							MAX_PATH );
		strDllPath.ReleaseBuffer();
		strDllPath = strDllPath.Left( strDllPath.ReverseFind(_T('\\'))+1 );
		strDllPath += "DbServer.EXE";

		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);

		BOOL fServerCreated = ::CreateProcess(
						strDllPath,
						NULL,		// Command line
						NULL,		// Process Security
						NULL,		// Thread Security
						FALSE,		// No Inherit
						DETACHED_PROCESS,
						NULL,		// Environment
						NULL,
						&si,
						&pi
					);
		if (!fServerCreated)
		{
			*pCtxt << _T("CreateProcess failed calling DbServer.<p>");
			EndContent(pCtxt);
			return;
		}
	}
	// DbServer may be starting up now, so wait for it.
	if (::WaitForSingleObject(serverRunning, TIMEOUT_EVENT) == WAIT_TIMEOUT)
	{
        *pCtxt << _T("DbServer failed to start.<p>");
	    EndContent(pCtxt);
		return;
	}

	// This mutex is only used within the Web server,
	// so it should not need world security attributes.
    CMutex myMutex(FALSE, MUTEX_DB_REQUEST);
    CSingleLock myLock(&myMutex, FALSE);

    // Wait to get access to DbServer
    // If another request is outstanding then we will not get in.
    if (myLock.Lock(TIMEOUT_MUTEX))
    {
        // Create events for signalling DbServer
        CEvent startEvent(FALSE, TRUE, EVENT_START_PROCESSING, &sa);
        CEvent doneEvent(FALSE, TRUE, EVENT_DONE_PROCESSING, &sa);

        // 
        // Allocate memory for our data structure in shared memory.
        // 
        HANDLE hFileMapping = NULL;
        DbRequest* pDbRequest = NULL;

        MTVERIFY( hFileMapping = ::CreateFileMapping((LPVOID) -1, &sa, 
            PAGE_READWRITE, 0, sizeof(DbRequest), 
            FILE_DB_REQUEST));

        MTVERIFY( pDbRequest = (DbRequest*) ::MapViewOfFile(hFileMapping,
            FILE_MAP_ALL_ACCESS, 0, 0, 0));

        //
        // Fill in our DB request.
        // Make sure we detect the default argument "~" and replace it.
        //
        strcpy(pDbRequest->sqlFilter, "");
        if (strcmp(pszFilter, "~") != 0)
            strcpy(pDbRequest->sqlFilter, pszFilter);

        strcpy(pDbRequest->sqlSort, "");
        if (strcmp(pszSort, "~") != 0)
            strcpy(pDbRequest->sqlSort, pszSort);

        // Tell DbServer to do the DB Query
        startEvent.SetEvent();

        // Wait for result from DbServer
        // If Server has died, we can tell user
        CSingleLock waitForDoneEvent(&doneEvent, FALSE);
        if (waitForDoneEvent.Lock(TIMEOUT_EVENT))
        {   // got result from server
            *pCtxt << _T("The following books match your search request:<p>");
            *pCtxt << pDbRequest->sqlResult << "<p>";
        }   // end if
        else
        {   // Got no response from server
            *pCtxt << _T("Sorry, but DbServer never responded with the results.<p>");
        }   // end else
        doneEvent.ResetEvent();

        // Close request data structure
        UnmapViewOfFile(pDbRequest);
        CloseHandle(hFileMapping);

    } // end if
    else
        {   // Another Thread is busy accessing the server
            *pCtxt << _T("Sorry, another Web Page is busy making a database request.<p>");
        }   // end else


    EndContent(pCtxt);
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CIs2OdbcExtension, CHttpServer)
    //{{AFX_MSG_MAP(CIs2OdbcExtension)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif  // 0



///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
    return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
                    LPVOID lpReserved)
{
    if (ulReason == DLL_PROCESS_ATTACH)
    {
        g_hInstance = hInst;
    }

    return TRUE;
}

****/
