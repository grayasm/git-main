/*
 * EventTst.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This sample is dicussed in Chapter 4, but there is
 * no associated listing.
 *
 * Watch the results of using an event object.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "MtVerify.h"

//
// Macro definitions
//
#define MAX_THREADS 3
#define EVENT_NAME "Event Test Object"

#define WM_PLEASE_DISPLAY WM_APP

// Used by the worker threads to ask the dialog to add an entry to the listbox.
#define AddToList(s) SendMessage(hDlgMain, WM_PLEASE_DISPLAY, 0, (LONG)s)


//
// Global Variables:
//
HANDLE hInst;
HANDLE hEventObject;

// HWND of the main dialog window so other threads can find it.
HWND hDlgMain;

// Remember the HANDLES to each of the threads.
HANDLE gThreads[3];
int threadId;

//
// Function declarations
//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK MainWndProc(HWND hWnd, unsigned msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EventDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
void StartThreads();
void KillThreads();
DWORD WINAPI ThreadProc(LPVOID n);

BOOL EventDlg_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam);
void EventDlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);


///////////////////////////////////////////////////////////
//
//		WinMain
//
// Main entry point of application. This will be a
// dialog based app, not a normal window, so this
// routine acts a little differently than "normal".
//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;
	HWND	hWnd;
	WNDCLASS wc;

	hInst = hInstance;
	if (!hPrevInstance)
	{
		memset(&wc, 0, sizeof(wc));
		wc.lpfnWndProc	= MainWndProc;
		wc.hInstance	= hInstance;
		wc.hIcon		= LoadIcon (hInstance, "GenIco");
		wc.hCursor		= LoadCursor(NULL,IDC_ARROW);
		wc.hbrBackground= GetSysColorBrush(COLOR_BACKGROUND);
		wc.lpszMenuName = "EVENTTSTMENU";
		wc.lpszClassName= "EventDlgClass";
		if (!RegisterClass(&wc))
			return FALSE;
	}
	
	
	hWnd = CreateWindow(
		"EventDlgClass",
		"Event Object Hands-On",
		WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
		CW_USEDEFAULT, //At this point we do not want to show
		0,             //the winddow until we know how big
		0,             //the Dialog Box is so that we can "FIT"
		0,             //the main window around it.
		NULL,
		NULL,
		hInstance,
		NULL);
	
	hDlgMain = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EVENT), hWnd, EventDlgProc);
	
	ShowWindow(hWnd, nCmdShow);
	ShowWindow(hDlgMain, SW_SHOW);
	
	
	while (GetMessage (&msg, NULL, 0, 0))
	{
		if(hDlgMain == NULL || !IsDialogMessage(hDlgMain,&msg))
		{
			TranslateMessage(&msg); /* Translate virtual key codes */
			DispatchMessage(&msg);	/* Dispatches message to window */
		}
	}
	return (msg.wParam);  /* Returns the value from
	PostQuitMessage */
}

LRESULT CALLBACK MainWndProc(HWND hWnd, unsigned msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;
		
	case WM_COMMAND:

		switch (wParam)
		{
		case IDM_ABOUT:
			DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
		default:
			return (DefWindowProc(hWnd, msg, wParam, lParam));
		}
		
	case WM_SETFOCUS:
		SetFocus(hDlgMain); // insure that the Dialog Box has the focus
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	default:
		return (DefWindowProc(hWnd, msg, wParam, lParam));
		
	}
	return 0;
}


//
//  About WndProc
//
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
			break;

		default:
			return (DefWindowProc(hDlg, message, wParam, lParam));
	}

    return FALSE;
}


LRESULT CALLBACK EventDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hctlListbox;
	
	switch (uMsg)
	{
	case WM_PLEASE_DISPLAY:
		hctlListbox = GetDlgItem(hDlg, IDC_RESULTS);
		ListBox_SetTopIndex(hctlListbox, ListBox_AddString(hctlListbox, lParam));
		break;

	case WM_CLOSE:
		DestroyWindow(hDlg);
		hDlgMain = NULL;
		break;
		
	case WM_DESTROY:
		return TRUE;
		break;
			
	HANDLE_MSG(hDlg, WM_INITDIALOG, EventDlg_OnInitDialog);
	HANDLE_MSG(hDlg, WM_COMMAND, EventDlg_OnCommand);

	default:
		return (FALSE);
	}

	return 0;
}

BOOL EventDlg_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam)
{
	HWND hctl;
	RECT rect;

	// Size parent to fit this dialog
	GetWindowRect(hwndDlg, &rect); 
	
	SetWindowPos(GetParent(hwndDlg),NULL,
		0,0,
		rect.right-rect.left,
		rect.bottom-rect.top+GetSystemMetrics(SM_CYMENU)
		+GetSystemMetrics(SM_CYCAPTION),
		SWP_NOMOVE | SWP_NOZORDER);
	
	hctl = GetDlgItem(hwndDlg, IDC_AUTOMATIC);
	Button_SetCheck(hctl, TRUE);
	PostMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDC_AUTOMATIC, BN_CLICKED), (LPARAM)hctl);

	return TRUE;
}


void EventDlg_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	int rc;

	switch (id)
	{
	case IDC_AUTOMATIC:
		KillThreads();
		if (hEventObject) rc = CloseHandle(hEventObject);
		MTVERIFY( hEventObject = CreateEvent(NULL,	// Security
										FALSE,		// Automatic (FALSE = not manual)
										0,			// Clear on creation
										"EventTest")// Name of object
									);
		// CreateEvent ALWAYS sets the last error
		if (GetLastError() == ERROR_ALREADY_EXISTS)
			AddToList("WARNING: Event wasn't destroyed");
		StartThreads();
		AddToList("Event set to AUTOMATIC");
		break;

	case IDC_MANUAL:
		KillThreads();
		if (hEventObject) rc = CloseHandle(hEventObject);
		MTVERIFY( hEventObject = CreateEvent(NULL,	// Security
										TRUE,		// Manual
										0,			// Clear on creation
										"EventTest")// Name of object
									);
		if (GetLastError() == ERROR_ALREADY_EXISTS)
			AddToList("Reusing old event");
		StartThreads();
		AddToList("Event set to MANUAL");
		break;

	case IDC_SIGNAL:
		MTVERIFY( SetEvent(hEventObject) );
		break;

	case IDC_RESET:
		MTVERIFY( ResetEvent(hEventObject) );
		break;

	case IDC_PULSE:
		MTVERIFY( PulseEvent(hEventObject) );
		break;

	case IDC_CLEAR:
		ListBox_ResetContent(GetDlgItem(hDlg, IDC_RESULTS));
		break;

	case IDCANCEL:
	case IDM_EXIT:
		PostMessage(GetParent(hDlg),WM_DESTROY, (WPARAM)0, (LPARAM)0);
		DestroyWindow(hDlgMain);
		hDlgMain = NULL;
		break;
		
	default:
		break;
	}
}

///////////////////////////////////////////////////////////
//
//		StartThreads
//
// Create the threads that will be waiting on the 
// event object. Each thread is passed its number.
//
void StartThreads()
{
	int i;
	for (i=0; i<MAX_THREADS; i++)
	{
		MTVERIFY( gThreads[i] = CreateThread(NULL,
			0,
			ThreadProc,
			(LPVOID)i,
			0,
			&threadId ) );
	}
}


///////////////////////////////////////////////////////////
//
//		KillThreads
//
// Terminate all of the threads that are waiting, because
// we are about to create a new event object.
//
// The threads own no resources, so calling TerminateThread
// thread on them should be fairly safe.
//
// Note that if we do not explicitly wait for the thread
// to exit with WaitForSingleObject, then the OS does not
// have time to clean up the event object and it will still
// be there when we try and open a new one.
//
void KillThreads()
{
	int i;
	for (i=0; i<MAX_THREADS; i++)
	{
		if (gThreads[i] != NULL)
		{
			TerminateThread(gThreads[i], 0);
			WaitForSingleObject(gThreads[i], INFINITE);
			CloseHandle(gThreads[i]);
			gThreads[i] = NULL;
		}
	}
}


///////////////////////////////////////////////////////////
//
//		ThreadProc
//
// This is the entry point for new threads. Make an entry
// in the log that this thread is about to wait, then go to
// sleep waiting on the event object. When we wake up,
// tell the user and go back to sleep.
//
// We Sleep briefly after the event is signaled to prevent
// the app from generating thousands of wakeup messages with
// with manual events.
//
DWORD WINAPI ThreadProc(LPVOID n)
{
	char buf[80];

	for (;;)
	{
		wsprintf(buf, "Thread #%d calling WaitForSingleObject", n);
		AddToList(buf);
		Sleep(100);
		MTVERIFY( WaitForSingleObject(hEventObject, INFINITE) != WAIT_FAILED );
		wsprintf(buf, "Thread #%d woke up", n);
		AddToList(buf);
	}
	return 0;
}


