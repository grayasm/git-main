// Main program for bugcheck driver
// Copyright (C) 1999, 2000 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

KBUGCHECK_CALLBACK_RECORD bugrecord;
ULONG bugbuffer;

VOID BugcheckCallback(PULONG buffer, ULONG bufsize);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath)
	{							// DriverEntry

	// Register a bug-check callback routine

	KeInitializeCallbackRecord(&bugrecord);
	KeRegisterBugCheckCallback(&bugrecord, (PKBUGCHECK_CALLBACK_ROUTINE) BugcheckCallback,
		&bugbuffer, sizeof(bugbuffer), (PUCHAR) "BUGCHECK");

	// Cause a bug check

	KeBugCheckEx(0x1234, 0, 1, 2, 3);
	}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID BugcheckCallback(PULONG buffer, ULONG bufsize)
	{							// BugcheckCallback
	*buffer = 42;
	}							// BugcheckCallback