#include "stdafx.h"
#include "Webcam.h"

#using <mscorlib.dll>
#using <PresentationFramework.dll>
#using <WindowsBase.dll>
#using <PresentationCore.dll>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Interop;
using namespace System::Runtime::InteropServices;

ref class MyHwndHost : HwndHost
{
protected: 
	virtual HandleRef BuildWindowCore(HandleRef hwndParent) override
	{
		HWND hwnd = CreateWindow(L"WebcamClass",			// Registered class
						NULL,								// Title
						WS_CHILD,							// Style
						CW_USEDEFAULT, 0,					// Position
						Webcam::GetWidth(),					// Width
						Webcam::GetHeight(),				// Height
						(HWND)hwndParent.Handle.ToInt32(),	// Parent
						NULL,								// Menu
						GetModuleHandle(NULL),				// hInstance
						NULL);								// Optional parameter

		if (hwnd == NULL)
			throw gcnew ApplicationException("CreateWindow failed!");

		Webcam::AttachToWindow(hwnd);

		return HandleRef(this, IntPtr(hwnd));
	}

	virtual void DestroyWindowCore(HandleRef hwnd) override
	{
		// Just a formality:
		::DestroyWindow((HWND)hwnd.Handle.ToInt32());
	}
};

ref class Window1 : Window
{
public:
	Window1()
	{
		DockPanel^ panel = gcnew DockPanel();
		MyHwndHost^ host = gcnew MyHwndHost();
		Label^ label = gcnew Label();
		label->FontSize = 20;
		label->Content = "The Win32 control is docked to the left.";
		panel->Children->Add(host);
		panel->Children->Add(label);
		this->Content = panel;

		if (FAILED(Webcam::Initialize(640, 480)))
			::MessageBox(NULL, L"Failed to communicate with a video capture device.", L"Error", 0);
		Webcam::Start();
	}

	~Window1()
	{
		Webcam::Terminate();
	}
};