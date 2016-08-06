/*
 * DbServer.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 16.
 *
 * DbServer is a process outside of the Internet
 * Information Server that processes requests from
 * Is2odbc in a fashion that will guarantee single-
 * threaded access to the JET engine.
 *
 * This process will be automatically started by
 * is2odbc.dll if it detects that DbServer.EXE
 * is not running.
 *
 * We cannot use MTVERIFY because this program does
 * not run under the desktop - it is loaded from a
 * service and so has a life of its own. Therefore
 * normal message boxes will not show up if something
 * fails.
 *
 * This server is intended to run forever because
 * we never get a shutdown message.  Note that this
 * process is VERY difficult to kill because the
 * user's desktop does not own this process.
 */

#include "stdafx.h"

//
// Include definition of Database Classes
//
#include "BookSet.h"

// Include the shared information between the Is2Odbc DLL and us
#include "..\Request.h"
#include "MtVerify.h"

CWinApp theApp;

//
// Setup a security descriptor that allows world access
//
SECURITY_DESCRIPTOR sd;
SECURITY_ATTRIBUTES sa;

void Log(char *msg)
{
	time_t ltime;
	time( &ltime );

	// Note that we keep appending to the end.
	// We keep opening and closing so that nothing
	// will be lost if the program crashes.
	FILE *fp = fopen("c:\\DbServer.log", "a");
	fprintf(fp, "DbServer: (%s) %s\n", ctime(&ltime), msg );
	fclose(fp);
}

//
// Define a main function to act as our server
//
int main()
{
	Log("Started");

    // Create a security descriptor that allows anyone
    //  to get at the event.  Otherwise the DLL and DbServer
	//  will get "access denied" trying to share data.
    if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
	{
		Log("InitializeSecurityDescriptor failed");
		return EXIT_FAILURE;
	}

    // Add a NULL disc. ACL to the security descriptor.
    //
    if (!SetSecurityDescriptorDacl(&sd, TRUE, (PACL) NULL, FALSE))
	{
		Log("SetSecurityDescriptorDacl failed");
		return EXIT_FAILURE;
	}

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = &sd;
    sa.bInheritHandle = FALSE;

	// If you are trying to debug DbServer.exe with IIS
	// running as a foreground process, this DebugBreak()
	// will let you get to the debugger.
	//DebugBreak();

	//
	// Open the DB Records that will be used
	///
	CAwBooksSet bookSet;

	// We do not really need to open the recordset here,
	// but it allows us to trap fatal open errors.
	try {
		if (!bookSet.Open())
		{
			Log("Failed to open book recordset");
			return EXIT_FAILURE;
		}
	}
	catch (CDBException* e)
	{
		char buf[256];
		e->GetErrorMessage(buf, 256);
		Log(buf);
		e->Delete();
		return EXIT_FAILURE;
	}

	Log("Initialized");

	// After being launched by the DLL, we need to set an event
	// to indicate that we are running. That event should have
	// been created by the DLL. If the event cannot be found,
	// loop and keep trying to open it.
	HANDLE hEvent;
	for (;;)
	{
		hEvent = ::OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_SERVER_RUNNING);
		if (hEvent)
			break;
		DWORD dwErr = ::GetLastError();
		if ( dwErr != ERROR_FILE_NOT_FOUND)
		{
			char buf[256];
			wsprintf(buf, "Received fatal error %d", dwErr);
			Log(buf);
			return EXIT_FAILURE;
		}
		// Put in a delay so this doesn't because a
		// tight loop and a CPU hog.
		Sleep(500);
	}
	::SetEvent(hEvent);

	Log("Finished handshake with DLL - Server ready");

	//
	// Create events for signalling the Is2Odbc DLL
	// 
	HANDLE hStartEvent = NULL;
	HANDLE hDoneEvent =  NULL;

	MTVERIFY( hStartEvent = ::CreateEvent(&sa, TRUE, FALSE, EVENT_START_PROCESSING));
	MTVERIFY( hDoneEvent =  ::CreateEvent(&sa, TRUE, FALSE, EVENT_DONE_PROCESSING));
	if (!hStartEvent || !hDoneEvent)
	{
		Log("Could not create events!");
		return -1;
	}

	//
	// Handle all incoming requests
	//
	DWORD dwResult;
	do
	{
		//
		// Wait until the IS2ODBC DLL tells us to start processing
		//
		dwResult = ::WaitForSingleObject(hStartEvent, INFINITE);
		if (dwResult == WAIT_OBJECT_0)
		{	// Got a request from the Is2Odbc DLL
			::ResetEvent(hStartEvent);

			// Get a pointer to the DB Request
			HANDLE hFileMapping = NULL;
			DbRequest* pDbRequest = NULL;

			MTVERIFY( hFileMapping = ::OpenFileMapping(
				FILE_MAP_ALL_ACCESS, FALSE, FILE_DB_REQUEST));

			MTVERIFY( pDbRequest = (DbRequest*) MapViewOfFile(hFileMapping,
				FILE_MAP_ALL_ACCESS, 0, 0, 0));

			//
			// Use exception handling to make sure DB request is handled correctly
			TRY
			{
				// Filter, parameterize and sort the section recordset
				bookSet.m_strFilter = pDbRequest->sqlFilter;
				bookSet.m_strSort = pDbRequest->sqlSort;

				BOOL bResult = FALSE;
				if (bookSet.IsOpen())
					bResult = bookSet.Requery();
				else
					bResult = bookSet.Open();
				if (bResult)
				{	// Add all the results to the request's result field
					char *pszOut = pDbRequest->sqlResult;
					while (!bookSet.IsEOF())
					{
						sprintf(pszOut, "(%s) %s, by %s<p>", bookSet.m_Category, bookSet.m_Title, bookSet.m_Author);
						pszOut += strlen(pszOut);
						bookSet.MoveNext();
					}	// end while
					bookSet.Close();
				}	// end if
			}	// end try
			CATCH(CDBException, e)
			{
				char buf[256];
				e->GetErrorMessage(buf, 256);
				sprintf(pDbRequest->sqlResult, "%s<p>", buf);
				bookSet.Close();
				e->Delete();
			}	// end catch
			END_CATCH

			// Signal Caller that request is done.
			SetEvent(hDoneEvent);

			// Close request data structure
			UnmapViewOfFile(pDbRequest);
			CloseHandle(hFileMapping);

		}	// end if

		//  only stay in loop if things are working correctly
	} while (dwResult == WAIT_OBJECT_0); 

	::CloseHandle(hEvent);
	::CloseHandle(hStartEvent);
	::CloseHandle(hDoneEvent);

	return 0;
}
