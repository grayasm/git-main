/*
 * Entry.cpp
 *
 * Demonstrates a very simple DLL that prints status messages when its
 * functions are called. It provides a single entry point called
 * TheFunction() for test purposes.
 */

#include <windows.h>
#include <stdio.h>

BOOL WINAPI DllMain(
				HINSTANCE	hinstDLL,		// handle to DLL module
				DWORD		fdwReason,		// reason for calling function
				LPVOID		lpReserved)		// reserved
{
	DWORD tid = GetCurrentThreadId();

	// why are we being called ?
	switch( fdwReason )
	{
	case DLL_PROCESS_ATTACH:
		/*
		DllMain is called automatically as a side effect of CreateProcess or CreateThread.
		If there are ten,twenty DLLs attached to the process suddenly we are looking at a 
		lot of overhead to perform the bookkeeping. To help avoid this problem we can call:
		
		DisableThreadLibraryCalls(hinstDLL);
		*/
		printf("DLL:\tProcess attach, tid= %d\n", tid);
		break;

	case DLL_THREAD_ATTACH:
		printf("DLL:\tThread  attach, tid= %d\n", tid);
		break;

	case DLL_THREAD_DETACH:
		printf("DLL:\tThread  detach, tid= %d\n", tid);
		break;

	case DLL_PROCESS_DETACH:
		printf("DLL:\tProcess detach, tid= %d\n", tid);
		break;
	}
	return TRUE;
} // DllMain


_declspec (dllexport) BOOL TheFunction()
{
	printf("DLL:\t%s called\n", __FUNCTION__);
	return TRUE;
} // TheFunction