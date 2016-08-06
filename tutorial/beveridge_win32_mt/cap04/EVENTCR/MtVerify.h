/*
 * MtVerify.h
 * Error handling for applications in
 * "Multithreading Applications in Win32"
*/

#include <windows.h>
#include <stdlib.h>


#define MTVERIFY(a)					\
	if(!(a)) {						\
	PrintError(#a, __FILE__,__LINE__,GetLastError());	\
	}

__inline void PrintError(LPSTR linedesc, LPSTR filename, int lineno, DWORD errnum)
{
	LPSTR lpBuffer;
	char errbuf[256];
#ifdef _WINDOWS
	char modulename[MAX_PATH];
#else // _WINDOWS
	DWORD numread;
#endif // _WINDOWS

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errnum,
		LANG_NEUTRAL,
		(LPTSTR)&lpBuffer,
		0,
		NULL);

	wsprintf(errbuf,
		"\nThe following call failed at line %d in %s:\n\n"
		"    %s\n\n"
		"Reason: %s\n",
		lineno, filename, linedesc, lpBuffer);


#ifndef _WINDOWS
	WriteFile(GetStdHandle(STD_ERROR_HANDLE),
		errbuf, strlen(errbuf), &numread, FALSE);
	Sleep(3000);
#else
	GetModuleFileName(NULL, modulename, MAX_PATH);
	MessageBox(NULL, errbuf, modulename, 
		MB_ICONWARNING|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND);
#endif

	/* Exit using a value appropriate for the operating system. */
	exit(EXIT_FAILURE);
}