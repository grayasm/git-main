/*
	KmdResource.h -- Declarations for kernel-mode driver resource package
	Copyright (C) 2001 by Walter Oney
*/


// The following type declarations are needed so we can include winver.h

typedef USHORT WORD;
typedef ULONG DWORD;
#undef TEXT
#define TEXT(s) L##s
#define APIENTRY
typedef ULONG UINT;
typedef UINT* PUINT;
typedef ULONG* LPDWORD;
typedef ULONG BOOL;
typedef PVOID LPVOID;
typedef CONST LPVOID *LPCVOID;

#include <winver.h>

/*	
	The kernel-mode resource package allows you to access resource objects in
	a kernel-mode driver whose service key name you know. To use the package,
	you need the following files in your driver project (see the RESOURCE
	sample supplied in Service Pack 8 to Programming the Microsoft Windows
	Driver Model):
		KmdResource.h (this file)
		KmdResource.cpp
		FileIo.cpp (from the FILEIO sample)
		FileIo98.cpp (ditto, and note the build requirements for that file!)
*/


#ifndef KMDRESOURCE_H
#define KMDRESOURCE_H

/*
	The first step in accessing resources is to open the image file for the
	driver (the resources are not mapped into the kernel-mode image). You can
	use one of the following functions to do that, depending on
	what you know about the file:

	(1) the name of the service key in the registry
	[i.e., the RegistryPath parameter to DriverEntry], 
	
	(2) the name of the service itself, or 
	
	(3) the pathname of the driver. 
	
	When you're done, call CloseDriverResources to close the file handle. 
	These functions can be called at PASSIVE_LEVEL only.
*/

NTSTATUS OpenDriverResourcesFromRegistry(PUNICODE_STRING RegistryPath, PHANDLE pHandle);
NTSTATUS OpenDriverResourcesFromService(PUNICODE_STRING ServiceName, PHANDLE pHandle);
NTSTATUS OpenDriverResourcesFromPathname(PUNICODE_STRING PathName, PHANDLE pHandle);

VOID CloseDriverResources(HANDLE hDriverResources);

/*
	Use this function to locate a specific resource. This is very similar to the
	user-mode function of the same name, except that it returns the address of the
	raw resource data directory without any extra steps. The caller should *not*
	release the memory to which the return value points.
*/

PVOID FindResourceEx(HANDLE hDriverResources, PWCHAR type, PWCHAR name, USHORT langid, ULONG& size);

/*	Functions for working with a version resource in a driver (cf. GetFileVersionInfo
	and VerQueryValue in the SDK)
*/

PVOID GetDriverVersionInfo(HANDLE hDriverResources);
PVOID VerQueryValue(PVOID pVersionResource, PWCHAR szSubBlock, ULONG& size);


// Useful declarations from user-mode headers

#define MAKEINTRESOURCE(i) (PWCHAR) ((ULONG_PTR) ((USHORT) (i)))

#define RT_CURSOR           MAKEINTRESOURCE(1)
#define RT_BITMAP           MAKEINTRESOURCE(2)
#define RT_ICON             MAKEINTRESOURCE(3)
#define RT_MENU             MAKEINTRESOURCE(4)
#define RT_DIALOG           MAKEINTRESOURCE(5)
#define RT_STRING           MAKEINTRESOURCE(6)
#define RT_FONTDIR          MAKEINTRESOURCE(7)
#define RT_FONT             MAKEINTRESOURCE(8)
#define RT_ACCELERATOR      MAKEINTRESOURCE(9)
#define RT_RCDATA           MAKEINTRESOURCE(10)
#define RT_MESSAGETABLE     MAKEINTRESOURCE(11)

#define DIFFERENCE          11
#define RT_GROUP_CURSOR MAKEINTRESOURCE((ULONG_PTR)RT_CURSOR + DIFFERENCE)
#define RT_GROUP_ICON   MAKEINTRESOURCE((ULONG_PTR)RT_ICON + DIFFERENCE)
#define RT_VERSION      MAKEINTRESOURCE(16)
#define RT_DLGINCLUDE   MAKEINTRESOURCE(17)
#define RT_PLUGPLAY     MAKEINTRESOURCE(19)
#define RT_VXD          MAKEINTRESOURCE(20)
#define RT_ANICURSOR    MAKEINTRESOURCE(21)
#define RT_ANIICON      MAKEINTRESOURCE(22)
#define RT_HTML         MAKEINTRESOURCE(23)

#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))


#endif