#include "stdafx.h"
#include "HostingWPF.h"
#include "commctrl.h"

#using <PresentationFramework.dll>
#using <PresentationCore.dll>
#using <WindowsBase.dll>

LRESULT CALLBACK DialogFunction(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	    case WM_INITDIALOG:
		{
			System::Windows::Interop::HwndSourceParameters p;
			p.WindowStyle = WS_VISIBLE | WS_CHILD;
			p.PositionX = 10;
			p.PositionY = 10;
			p.Width = 500;
			p.Height = 350;
			p.ParentWindow = System::IntPtr(hDlg);

			System::Windows::Interop::HwndSource^ source = gcnew System::Windows::Interop::HwndSource(p);        
			source->RootVisual = gcnew System::Windows::Controls::DocumentViewer();
            return TRUE;
		}

		case WM_CLOSE:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
    }
    return FALSE;
}

[System::STAThreadAttribute]
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    DialogBox(hInstance, (LPCTSTR)IDD_MYDIALOG, NULL, (DLGPROC)DialogFunction);
    return 0;
}