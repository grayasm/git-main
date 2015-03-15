/*
 * stdafx.h : header file
 *
 * Sample code for "Multitasking in Win32"
 * This is from Chapter 16???
 *
 * include file for standard system include files,
 * or project specific include files that are used frequently, but
 * are changed infrequently
 */

//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define _WIN32_WINNT 0x0400 // for CoInitializeEx function prototype

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//
// Include Definition from ComDemo DLL
//
#include "..\ComDemo.h"
