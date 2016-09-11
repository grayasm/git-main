// samclass.cpp -- Property page provider and class installer for the SAMPLE class of devices
// Copyright (C) 1999, 2001 by Walter Oney
// All rights reserved
//
// This file, which was revised in SP-9, illustrates the basic mechanics of
// a property page provider and a custom icon for a device class. Note that
// you don't need both pieces of functionality: you could have a (tiny!) DLL
// with just the class installer function or a DLL with just an EnumPropPages
// function.

#include "StdAfx.h"
#include "resource.h"



HINSTANCE hInst;
BOOL WINAPI PageDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
UINT CALLBACK PageCallbackProc(HWND junk, UINT msg, LPPROPSHEETPAGE p);

struct SETUPSTUFF 
{
	HDEVINFO info;
	PSP_DEVINFO_DATA did;
	char infopath[MAX_PATH];
};

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif


BOOL APIENTRY DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
{
	hInst = (HINSTANCE) hModule;
	return TRUE;
}


/*
	This function is the "class installer" for the sample class. 
	The function is obviously trivial -- its only purpose is to allow us 
	to provide a custom icon for the "sample" class of device. 
	
	This function is specifically exported in the .DEF file, which is required 
	in lieu of just using __declspec(dllexport) in the definition of the 
	function to avoid the __stdcall name decoration.
	In addition, the class key for "sample" specifies this dll and function
	by name as the Installer32 value.
*/

extern "C" DWORD CALLBACK SampleClassInstaller(DI_FUNCTION fcn, HDEVINFO infoset, PSP_DEVINFO_DATA did)
{

#if _DEBUG
	static char* difname[] = {
		"0",
		"DIF_SELECTDEVICE",
		"DIF_INSTALLDEVICE",
		"DIF_ASSIGNRESOURCES",
		"DIF_PROPERTIES",
		"DIF_REMOVE",
		"DIF_FIRSTTIMESETUP",
		"DIF_FOUNDDEVICE",
		"DIF_SELECTCLASSDRIVERS",
		"DIF_VALIDATECLASSDRIVERS",
		"DIF_INSTALLCLASSDRIVERS",
		"DIF_CALCDISKSPACE",
		"DIF_DESTROYPRIVATEDATA",
		"DIF_VALIDATEDRIVER",
		"DIF_MOVEDEVICE",
		"DIF_DETECT",
		"DIF_INSTALLWIZARD",
		"DIF_DESTROYWIZARDDATA",
		"DIF_PROPERTYCHANGE",
		"DIF_ENABLECLASS",
		"DIF_DETECTVERIFY",
		"DIF_INSTALLDEVICEFILES",
		"DIF_UNREMOVE",
		"DIF_SELECTBESTCOMPATDRV",
		"DIF_ALLOW_INSTALL",
		"DIF_REGISTERDEVICE",
		"DIF_NEWDEVICEWIZARD_PRESELECT",
		"DIF_NEWDEVICEWIZARD_SELECT",
		"DIF_NEWDEVICEWIZARD_PREANALYZE",
		"DIF_NEWDEVICEWIZARD_POSTANALYZE",
		"DIF_NEWDEVICEWIZARD_FINISHINSTALL",
		"DIF_UNUSED1",
		"DIF_INSTALLINTERFACES",
		"DIF_DETECTCANCEL",
		"DIF_REGISTER_COINSTALLERS",
		"DIF_ADDPROPERTYPAGE_ADVANCED",
		"DIF_ADDPROPERTYPAGE_BASIC",
		"DIF_RESERVED1",
		"DIF_TROUBLESHOOTER",
		"DIF_POWERMESSAGEWAKE",
		};

	char msg[128];
	if (fcn < arraysize(difname))
		sprintf(msg, "SAMCLASS - %s\n", difname[fcn]);
	else
		sprintf(msg, "SAMCLESS - 0x%X\n", fcn);

	OutputDebugString(msg);
#endif // _DEBUG

	return ERROR_DI_DO_DEFAULT;	// do default action in all cases
	}							// SampleClassInstaller

///////////////////////////////////////////////////////////////////////////////
// This function is the "property page provider" for the sample class. The name of
// this DLL is the value of the EnumPropPages32 value in the "sample" class key.
// EnumPropPages is the name of the exported function that Device Manager searches
// for by default, but you could give it a different name if you wanted to.
//
// Note on control placement: The Device Manager's regular property pages place the
// icon at 7,7 and the device description at 37, 9. If you look carefully at the
// dialog resource, you'll see that I did the same thing, so that these controls
// don't appear to flop around as you page through the property sheet.

extern "C" BOOL CALLBACK EnumPropPages(PSP_PROPSHEETPAGE_REQUEST p,
	LPFNADDPROPSHEETPAGE AddPage, LPARAM lParam)
	{							// EnumPropPages
	PROPSHEETPAGE page;
	HPROPSHEETPAGE hpage;

	memset(&page, 0, sizeof(page));
	page.dwSize = sizeof(PROPSHEETPAGE);
	page.hInstance = hInst;
	page.pszTemplate = MAKEINTRESOURCE(IDD_SAMPAGE);
	page.pfnDlgProc = (DLGPROC) PageDlgProc;

	// Create an auxiliary data structure to pass important information
	// to our WM_INITDIALOG handler. Arrange for a callback when the page
	// is destroyed (the only event we actually care about) to delete this
	// structure

	SETUPSTUFF* stuff = new SETUPSTUFF;
	stuff->info = p->DeviceInfoSet;
	stuff->did = p->DeviceInfoData;
	page.lParam = (LPARAM) stuff;
	page.pfnCallback = PageCallbackProc;
	page.dwFlags = PSP_USECALLBACK;

	// Create a property page and add it to the device manager's property sheet

	hpage = CreatePropertySheetPage(&page);

	if (!hpage)
		{
		delete stuff;
		return TRUE;
		}

	if (!(*AddPage)(hpage, lParam))
		DestroyPropertySheetPage(hpage);

	return TRUE;
	}							// EnumPropPages

///////////////////////////////////////////////////////////////////////////////

BOOL WINAPI PageDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
	{							// PageDlgProc
	int flag = DWLP_DLGPROC + sizeof(DLGPROC); // DWL_USER;
	SETUPSTUFF* stuff = (SETUPSTUFF*) GetWindowLong(hdlg, flag);

	switch (msg)
		{						// process message

	case WM_INITDIALOG:
		{						// WM_INITDIALOG
		SETUPSTUFF* stuff = (SETUPSTUFF*) ((LPPROPSHEETPAGE) lParam)->lParam;
		SetWindowLong(hdlg, flag, (LONG) stuff);

		// Determine the friendly name or description of the device

		TCHAR name[256];
		if (!SetupDiGetDeviceRegistryProperty(stuff->info, stuff->did, SPDRP_FRIENDLYNAME, NULL, (PBYTE) name, sizeof(name), NULL)
			&& !SetupDiGetDeviceRegistryProperty(stuff->info, stuff->did, SPDRP_DEVICEDESC, NULL, (PBYTE) name, sizeof(name), NULL))
			name[0] = 0;

		SetDlgItemText(hdlg, IDC_SAMNAME, name);

		// Set the class icon

		HWND hClassIcon = GetDlgItem(hdlg, IDC_CLASSICON);
		HICON hIcon;
		if (SetupDiLoadClassIcon(&stuff->did->ClassGuid, &hIcon, NULL))
			SendMessage(hClassIcon, STM_SETICON, (WPARAM) (HANDLE) hIcon, 0);
		else
			ShowWindow(hClassIcon, SW_HIDE);

		// Determine the URL for the sample information file by interrogating the non-standard
		// device property SampleInfo. The user may click the More Information button on this
		// page to view this file in a web browser.

		HKEY hkey = SetupDiOpenDevRegKey(stuff->info, stuff->did, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
		DWORD length = sizeof(name);
		if (hkey && RegQueryValueEx(hkey, "SampleInfo", NULL, NULL, (LPBYTE) name, &length) == 0)
			{				// get sample info URL
    		DoEnvironmentSubst(name, sizeof(name));
			int len = strlen(name);
			if (len >= sizeof(stuff->infopath))
				len = sizeof(stuff->infopath) - 1;
			memcpy(stuff->infopath, name, len);
			stuff->infopath[len] = 0;

			RegCloseKey(hkey);
			}				// get sample info URL
		else
			{				// no sample info
			stuff->infopath[0] = 0;
			ShowWindow(GetDlgItem(hdlg, IDC_INFOLABEL), SW_HIDE);
			ShowWindow(GetDlgItem(hdlg, IDB_MOREINFO), SW_HIDE);
			}				// no sample info
			    		
    	break;
    	}						// WM_INITDIALOG
    	
    case WM_COMMAND:
    	switch (LOWORD(wParam))
    		{					// process command notification
    		
    	case IDB_MOREINFO:
    		{					// IDB_MOREINFO 
    		ShellExecute(hdlg, NULL, stuff->infopath, NULL, NULL, SW_SHOWNORMAL);
    		return TRUE;
    		}					// IDB_MOREINFO
    		
    		}					// process command notification
		break;

		}						// process message

	return FALSE;
	}							// PageDlgProc

///////////////////////////////////////////////////////////////////////////////

UINT CALLBACK PageCallbackProc(HWND junk, UINT msg, LPPROPSHEETPAGE p)
	{							// PageCallbackProc
	if (msg == PSPCB_RELEASE && p->lParam)
		delete (SETUPSTUFF*) p->lParam;
	return TRUE;				// matters only for PSPCB_CREATE
	}							// PageCallbackProc
