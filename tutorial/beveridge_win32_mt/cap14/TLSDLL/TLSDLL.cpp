/*
 * Chapter 14 - Building DLLs - Thread Local Storage
 *
 *
 * TLS is a mechanism whereby a thread can keep a pointer to its own copy of a 
 * data structure. Both the C run-time library and MFC use of TLS.
 * The C run-time keeps values such as errno and the strtok() pointer in a thread
 * local structure because their state must be preserved between calls without
 * interference between threads.
 *
 * MFC uses TLS to keep track of handles to GDI and USER objects (CWnd, CPen, etc)
 * on a per thread basis, and verifies that objects are not being passed between
 * threads.
 *
 * TLS works by giving each thread an array of 4-byte slots, guaranteed to have
 * at least TLS_MINIMUM_AVAILABLE entries in it.
 *
 * Use: TlsAlloc(), TlsSetValue(), TlsGetValue(), TlsFree()
 * Listing 14-4
 */

#include <windows.h>
#include <stdio.h>
#include "MtVerify.h"

// this is the shared slot
static DWORD gdwTlsSlot;

typedef struct _OurData
{
	DWORD dwValue;
} OurData ;


BOOL WINAPI DllMain(
				HINSTANCE	hinstDLL,		// handle to DLL module
				DWORD		fdwReason,		// reason for calling function
				LPVOID		lpReserved)		// reserved
{
	LPVOID		lpData;
	DWORD		threadId;
	UNREFERENCED_PARAMETER(hinstDLL);
	UNREFERENCED_PARAMETER(lpReserved);


	threadId = GetCurrentThreadId();

	switch( fdwReason )
	{
	case DLL_PROCESS_ATTACH:
		{
			// Find the index that will be global for all thread
			gdwTlsSlot = TlsAlloc();
			MTVERIFY( gdwTlsSlot != TLS_OUT_OF_INDEXES );
			if( gdwTlsSlot == TLS_OUT_OF_INDEXES )				
				return FALSE;
			// Fall through to handle thread attach too

			printf("\n\tDLL:\tProcess attach, tid: %d", threadId);
		}

	case DLL_THREAD_ATTACH:
		{
			// Initialize the TLS index for this thread.
			MTVERIFY( lpData = (LPVOID) LocalAlloc(LPTR, sizeof(OurData)) );
			if( lpData != NULL )
				MTVERIFY( TlsSetValue(gdwTlsSlot, lpData) );
					
			OurData* pData = (OurData*) lpData;
			pData->dwValue = threadId;

			printf("\n\tDLL:\tThread  attach, tid: %d", threadId);
		}
		break;

	case DLL_THREAD_DETACH:
		{
			// Releases the allocated memory for this thread
			MTVERIFY( lpData = TlsGetValue(gdwTlsSlot) );
			if( lpData != NULL )
				LocalFree((HLOCAL) lpData);

			printf("\n\tDLL:\tThread  detach, tid: %d", threadId);
		}
		break;

	case DLL_PROCESS_DETACH:
		{
			MTVERIFY( lpData = TlsGetValue(gdwTlsSlot) );
			if( lpData != NULL )
				LocalFree((HLOCAL)lpData);

			// Give back the TLS slot
			MTVERIFY( TlsFree(gdwTlsSlot) );

			printf("\n\tDLL:\tProcess detach, tid: %d", threadId);
		}
		break;

	default:
		break;
	}

	return TRUE;
} // main

_declspec(dllexport) BOOL TheFunction()
{
	DWORD	threadId;
	LPVOID	lpData;

	threadId = GetCurrentThreadId();
	MTVERIFY( lpData  = TlsGetValue(gdwTlsSlot) );

	if( lpData == NULL )
	{
		printf("\n\tThread id: %d, invalid TLS slot", threadId);
		return FALSE;
	}

	OurData* pOurData = (OurData*)lpData;
	if( threadId == pOurData->dwValue )
		printf("\n\tThread id: %d, TLS OK!!!", threadId);
	else
		printf("\n\tThread id: %d, TLS -----", threadId);

	return TRUE;
}
