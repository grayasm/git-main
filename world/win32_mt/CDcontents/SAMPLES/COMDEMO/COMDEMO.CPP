/*
 * ComDemo.cpp : Implementation of DLL Exports.
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 17
 *
 * !!! YOU MUST HAVE THE ActiveX Template Library
 * !!! TO BUILD THIS PROJECT.
 *
 * The ATL is free from Microsoft.
 *
 * Implements a FreeThreaded COM Object
 */

// You will need the NT SUR Beta 2 SDK or VC 4.2 in order to build this 
// project.  This is because you will need MIDL 3.00.15 or higher and new
// headers and libs.  If you have VC 4.2 installed, then everything should
// already be configured correctly.

// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f ComDemops.mak in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "ComDemo.h"
#include "AutoIncr.h"

#define IID_DEFINED
#include "ComDemo_i.c"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_CAutoIncr, CAutoIncr)
END_OBJECT_MAP()

class CComDemoApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CComDemoApp theApp;

BOOL CComDemoApp::InitInstance()
{
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();
}

int CComDemoApp::ExitInstance()
{
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}

