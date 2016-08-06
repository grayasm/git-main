// ShareMem.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ShareMem.h"
#include "ShareDlg.h"
#include "MtVerify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Global Variables

// This is the global pointer to the shared memory block.
// It will be initialized in InitInstance().
SharedBlock* gpSharedBlock;

// This mutex will protect the data so that only one
// process can access it at a time. It would be much
// better to use a readers/writers lock, but this
// is simpler for this example.
HANDLE		 ghDataLock;

/////////////////////////////////////////////////////////////////////////////
// CShareMemApp

BEGIN_MESSAGE_MAP(CShareMemApp, CWinApp)
	//{{AFX_MSG_MAP(CShareMemApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareMemApp construction

CShareMemApp::CShareMemApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShareMemApp object

CShareMemApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CShareMemApp initialization

BOOL CShareMemApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    // Create a mutex with initial ownership. If it already
    // exists, we will block until it is available.
    ghDataLock = ::CreateMutex(NULL, TRUE, "ShareMem Data Mutex");
    MTVERIFY( ghDataLock != NULL );

    HANDLE hFileMapping;

    hFileMapping = ::CreateFileMapping(
                        (HANDLE)0xFFFFFFFF,  // File handle
                        NULL,                // Security attributes
                        PAGE_READWRITE,      // Protection
                        0,                   // Size - high 32 bits
                        1<<16,               // Size - low 32 bits
                        "ShareMem Sample App Data Block"); // Name
    MTVERIFY( hFileMapping != NULL );
    DWORD dwMapErr = GetLastError();

    gpSharedBlock = (SharedBlock*) ::MapViewOfFile(
                        hFileMapping,        // File mapping object
                        FILE_MAP_ALL_ACCESS, // Read/Write
                        0,                  // Offset - high 32 bits
                        0,                  // Offset - low 32 bits
                        0);                 // Map the whole thing
    MTVERIFY( gpSharedBlock != NULL );

    // Only initialize shared memory if we actually created.
    if (dwMapErr != ERROR_ALREADY_EXISTS)
        gpSharedBlock->m_nStringCount = 0;

    ::ReleaseMutex(ghDataLock);

    CShareMemDlg dlg;
    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();

    MTVERIFY( ::UnmapViewOfFile(gpSharedBlock) );
    MTVERIFY( ::CloseHandle(hFileMapping) );
    MTVERIFY( ::CloseHandle(ghDataLock) );

    // Since the dialog has been closed, return FALSE so that we exit the
    // application, rather than start the application's message pump.
	return FALSE;
}
