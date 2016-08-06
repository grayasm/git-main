/*
 * BackPrnt.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 2, Listing 2-3
 *
 * Demonstrates background printing
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include "resource.h"
#include "MtVerify.h"

//
// Macro definitions
//
#define WM_SHOWBITMAP   WM_APP

#define MAX_PRINT_JOBS  64


//
// Structures
//
typedef struct
{   // Information passed to background thread for printing
    HWND hDlg;
    HWND hWndParent;
    HDC hDc;
    BOOL bPrint;    // TRUE if printing;
    char szText[256];
} ThreadPrintInfo;

//
// Global variables
//
HANDLE hInst;
HBITMAP gbmpDisplay;
RECT gDisplayRect;

int gNumPrinting = 0;

// Handle to each created thread
HANDLE gPrintJobs[64];

// Height of bitmap returned by DrawText
int iHeight;

// HWND of the dialog so other threads can find it.
HWND hDlgMain;


//
// Function declarations
//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK MainWndProc(HWND hWnd, unsigned msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK PrintDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL PrintDlg_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam);
void PrintDlg_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
void PrintDlg_OnPaint(HWND hwnd);
void PrintText(HWND hwndParent, char *pszText);
void PrintToDisplay(HWND hwndParent, char *pszText);
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WINAPI BackgroundPrintThread(LPVOID pVoid);


///////////////////////////////////////////////////////////
//
//      WinMain
//
// Main entry point of application. This will be a
// dialog based app, not a normal window, so this
// routine acts a little differently than "normal".
//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG     msg;
    HWND    hWnd;
    WNDCLASS wc;
	int index;

    hInst = hInstance;
    if (!hPrevInstance)
    {
        memset(&wc, 0, sizeof(wc));
        wc.lpfnWndProc  = MainWndProc;
        wc.hInstance    = hInstance;
        wc.hIcon        = LoadIcon (hInstance, "GenIco");
        wc.hCursor      = LoadCursor(NULL,IDC_ARROW);
        wc.hbrBackground= GetSysColorBrush(COLOR_BACKGROUND);
        wc.lpszMenuName = "PRINTING_MENU";
        wc.lpszClassName= "PrintDlgClass";
        if (!RegisterClass(&wc))
            return FALSE;
    }


    hWnd = CreateWindow(
        "PrintDlgClass",
        "Background Printing",
        WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
        CW_USEDEFAULT, // At this point we do not want to
        0,             //  show the window until we know
        0,             //  how big the Dialog Box is so
        0,             //  that we can fit the main window
        NULL,          //  around it.
        NULL,
        hInstance,
        NULL);

    hDlgMain = CreateDialog(hInst,
                    MAKEINTRESOURCE(IDD_PRINT),
                    hWnd, PrintDlgProc);

    ShowWindow(hWnd, nCmdShow);
    ShowWindow(hDlgMain, SW_SHOW);

	while (GetMessage(&msg, NULL, 0, 0))
	{	// Get Next message in queue
		if(hDlgMain == NULL || !IsDialogMessage(hDlgMain,&msg))
		{
			TranslateMessage(&msg); /* Translate virtual key codes */
			DispatchMessage(&msg);	/* Dispatches message to window */
		}
	} // end while

	// Wait for all threads to terminate. The Window will
    // have already disappeared by this point.
	for (index = 0; index < gNumPrinting; index++)
	{
		DWORD status;
		do 
		{	// Wait for thread to terminate
			GetExitCodeThread(gPrintJobs[index], &status);
			Sleep(10);
		} while (status == STILL_ACTIVE);

	} // end for

	return (msg.wParam);  /* Returns the value from PostQuitMessage */
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
        // ensure that the Dialog Box has the focus
        SetFocus(hDlgMain);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);

    }
    return 0;
}


LRESULT CALLBACK PrintDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hDlg);
        hDlgMain = NULL;
        break;
        
    case WM_DESTROY:
        return TRUE;
        break;

    case WM_SHOWBITMAP:
        if (gbmpDisplay)
            DeleteObject(gbmpDisplay);

        gDisplayRect = *(RECT*)wParam;
        gbmpDisplay = (HBITMAP) lParam;
        InvalidateRect(hDlgMain, NULL, TRUE);
        break;

    HANDLE_MSG(hDlg, WM_INITDIALOG, PrintDlg_OnInitDialog);
    HANDLE_MSG(hDlg, WM_COMMAND, PrintDlg_OnCommand);
    HANDLE_MSG(hDlg, WM_PAINT, PrintDlg_OnPaint);

    default:
        return (FALSE);
    }

    return 0;
}

BOOL PrintDlg_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam)
{
    RECT rect;

    // Size parent to fit this dialog
    GetWindowRect(hwndDlg, &rect); 
    SetWindowPos(GetParent(hwndDlg),NULL,
        0,0,
        rect.right-rect.left,
        rect.bottom-rect.top+GetSystemMetrics(SM_CYMENU)
            +GetSystemMetrics(SM_CYCAPTION),
        SWP_NOMOVE | SWP_NOZORDER);

    return TRUE;
}

void PrintDlg_OnCommand(HWND hDlg, int id,HWND hwndCtl, UINT codeNotify)
{
    char szText[256];

    switch (id)
    {
    case IDC_PRINT:
        GetDlgItemText(hDlg, IDC_EDIT_TEXT, szText, 256);
        PrintText(hDlg, szText);
        break;

    case IDC_DISPLAY:
        GetDlgItemText(hDlg, IDC_EDIT_TEXT, szText, 256);
        PrintToDisplay(hDlg, szText);
        break;

    case IDCANCEL:
    case IDM_EXIT:
        PostMessage(GetParent(hDlg),WM_DESTROY,
                        (WPARAM)0, (LPARAM)0);
        DestroyWindow(hDlgMain);
        hDlgMain = NULL;
        break;
        
    default:
        break;
    }
}

void PrintDlg_OnPaint( HWND hwnd )
{
    PAINTSTRUCT paint;
    HWND hwndCtrl;
	HDC hdc;
    HDC hDcMem;
    HBITMAP bmpOld;
    RECT rect;
    POINT point;

	if (!gbmpDisplay)
		return;

    hwndCtrl = GetDlgItem(hwnd, IDC_OUTPUT);

    hdc = BeginPaint(hwnd, &paint);

    GetWindowRect(hwndCtrl, &rect);
    point = *((POINT *)&rect);
    ScreenToClient(hwnd, &point);

    hDcMem = CreateCompatibleDC(NULL);
    bmpOld = SelectObject(hDcMem, gbmpDisplay);

    // Copy bitmap to screen
    MTVERIFY( BitBlt(hdc, point.x+10, point.y+40,
        gDisplayRect.right-gDisplayRect.left, gDisplayRect.bottom-gDisplayRect.top,
        hDcMem, iHeight, 0, SRCCOPY) );

    SelectObject(hDcMem, bmpOld);
    DeleteDC(hDcMem);

    EndPaint(hwnd, &paint);
}

//
// Asks user which printer to use, then creates
// background printing thread.
//
void PrintText(HWND hwndParent, char *pszText)
{
    ThreadPrintInfo *pInfo;
    HANDLE hThread;
    DWORD dwThreadId;
    int result;
    DOCINFO docInfo;

    PRINTDLG dlgPrint;

    // Put up Common Dialog for Printing and get hDC.
    memset(&dlgPrint, 0, sizeof(PRINTDLG));
    dlgPrint.lStructSize = sizeof(PRINTDLG);
    dlgPrint.hwndOwner = hwndParent;
    dlgPrint.Flags = PD_ALLPAGES | PD_USEDEVMODECOPIES
           | PD_NOPAGENUMS | PD_NOSELECTION | PD_RETURNDC;
    dlgPrint.hInstance = hInst;
    if (!PrintDlg(&dlgPrint))
        return;

    // Initialize Printer device
    docInfo.cbSize = sizeof(DOCINFO);
    docInfo.lpszDocName = "Background Printing Example";
    docInfo.lpszOutput = NULL;
    docInfo.lpszDatatype = NULL;
    docInfo.fwType = 0;
    result = StartDoc(dlgPrint.hDC, &docInfo);
    result = StartPage(dlgPrint.hDC);

    pInfo = HeapAlloc(GetProcessHeap(),
                      HEAP_ZERO_MEMORY,
                      sizeof(ThreadPrintInfo));
    pInfo->hDlg = hwndParent;
    pInfo->hWndParent = hwndParent;
    pInfo->hDc = dlgPrint.hDC;
    pInfo->bPrint = TRUE;
    strcpy(pInfo->szText, pszText);

    MTVERIFY( hThread = CreateThread(NULL, 0,
        BackgroundPrintThread, (LPVOID)pInfo,
        0, &dwThreadId ));

	// keep track of all background printing threads
    gPrintJobs[gNumPrinting++] = hThread;
}

//
// Shows output on the dialog box.
//
void PrintToDisplay(HWND hwndParent, char *pszText)
{
    ThreadPrintInfo *pInfo;
    DWORD dwThreadId;
    HANDLE hThread;

    pInfo = HeapAlloc(GetProcessHeap(),
                      HEAP_ZERO_MEMORY,
                      sizeof(ThreadPrintInfo));
    pInfo->hDlg = hwndParent;
    pInfo->hWndParent = GetDlgItem(hwndParent, IDC_OUTPUT);
	pInfo->hDc = GetDC(pInfo->hWndParent);
    pInfo->bPrint = FALSE;
    strcpy(pInfo->szText, pszText);

    MTVERIFY( hThread = CreateThread(NULL, 0,
                                     BackgroundPrintThread,
                                     (LPVOID)pInfo,
                                     0, &dwThreadId ));

	// keep track of all background printing threads
    gPrintJobs[gNumPrinting++] = hThread;
}



//---------------------------------------------------------
// About Box Handling
//---------------------------------------------------------

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK
                || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, TRUE);
                return (TRUE);
            }
            break;

        default:
            return (DefWindowProc(hDlg, message, wParam, lParam));
    }

    return FALSE;
}


//---------------------------------------------------------
// Background Printing Code
//---------------------------------------------------------

DWORD WINAPI BackgroundPrintThread(LPVOID pVoid)
{
    ThreadPrintInfo *pInfo = (ThreadPrintInfo*) pVoid; 
    RECT rect;
    RECT rectMem;
    HDC hDcMem;
    HBITMAP bmpMem;
    HBITMAP bmpOld;
    int x, y;
    int counter = 0;
    int nHeight;
    HFONT hFont;
    HFONT hFontOld;

    // Get dimensions of paper into rect
    rect.left = 0;
    rect.top = 0;
    rect.right =  GetDeviceCaps(pInfo->hDc, HORZRES);
    rect.bottom = GetDeviceCaps(pInfo->hDc, VERTRES);

    nHeight = -MulDiv(36, GetDeviceCaps(pInfo->hDc, LOGPIXELSY), 72);

    // Create Font
    hFont = CreateFont(nHeight, 0, 
        0, 0, FW_DONTCARE, 
        FALSE, FALSE, FALSE, 
        ANSI_CHARSET, 
        OUT_TT_PRECIS, 
        CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY, 
        VARIABLE_PITCH,
        NULL);
    MTASSERT( hFont != 0);

    // Draw into memory device context
    hDcMem = CreateCompatibleDC(pInfo->hDc);
    hFontOld = SelectObject(hDcMem, hFont);
    iHeight = DrawText(hDcMem, pInfo->szText, -1,  &rect, DT_LEFT | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT);
    rectMem = rect;
    rectMem.left = rect.left + iHeight;
    rectMem.right = rect.right + (iHeight*2);
    bmpMem = CreateCompatibleBitmap(hDcMem,
                                    rectMem.right, rect.bottom);
    bmpOld = SelectObject(hDcMem, bmpMem);
    OffsetRect(&rect, iHeight, 0); 
    DrawText(hDcMem, pInfo->szText, -1,  &rect,
             DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);

    // Italicize bitmap. We use GetPixel and
    // SetPixel because they are horribly inefficient,
    // thereby causing the thread to run for awhile.
    for (y = 0; y < iHeight; y++)
    {   // Italicize line y
        for (x = rectMem.right; x > iHeight; x--)
        {   // Move specified pixel to the right.
            COLORREF color;
            int offset;
            offset = y - iHeight;
            color = GetPixel(hDcMem, x + offset, y);
            if (color != 0)
                counter++;
            SetPixel(hDcMem, x, y, color);
        } // end for x
    } // end for y
    MTASSERT( counter > 0);

    // Copy bitmap of italicized text from memory to device
    if (pInfo->bPrint)
    {
        BitBlt(pInfo->hDc, 50, 50, rectMem.right-rect.left, rectMem.bottom-rect.top,
            hDcMem, iHeight, 0, SRCCOPY);
    }

    SelectObject(hDcMem, hFontOld);
    SelectObject(hDcMem, bmpOld);
    DeleteDC(hDcMem);

    if (!pInfo->bPrint)
    {
        // We can't just write to the global variable where the
        // bitmap is kept or we might overwrite the work of
        // another thread, thereby "losing" a bitmap

        // Also, if we used PostMessage instead of SendMessage, then
        // the rectangle could have been deleted (it's on the stack)
        // by the time the main message loop is reached.
        SendMessage(pInfo->hDlg, WM_SHOWBITMAP, (WPARAM)&rectMem, (LPARAM) bmpMem);
    }

    if (pInfo->bPrint)
    {   // Finish printing
        int result;

        result = EndPage(pInfo->hDc);
        MTASSERT (result != SP_ERROR);
        result = EndDoc(pInfo->hDc);
        MTASSERT (result != SP_ERROR);
        DeleteDC(pInfo->hDc);
        // If we are printing, we are done with the bitmap.
        DeleteObject(bmpMem);
    } 
    else
    {
        ReleaseDC(pInfo->hWndParent, pInfo->hDc);
    }

    // free data structure passed in.
    HeapFree(GetProcessHeap(), 0, pInfo);

    return 0;
}
