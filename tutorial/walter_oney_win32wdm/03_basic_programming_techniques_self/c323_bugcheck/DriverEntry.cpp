/*
	c3_bugcheck main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.2.3 Bug Checks

	Unrecoverable errors in kernel mode can manifest themselves in the 
	so-called blue screen of death (BSOD).

	The main feature of a bug check (KeBugCheckEx) is that the system shuts 
	itself down in as orderly a way as possible and presents the BSOD. 
	Once the BSOD appears, the system is dead and must be rebooted.
*/

#include "driver.h"


#define DRIVERNAME "C3_BUGCHECK"

KBUGCHECK_CALLBACK_RECORD	bugrecord;
ULONG						bugbuffer;

VOID BugcheckCallback(PULONG buffer, ULONG bugsize);


#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	// Useless KdPrint at this stage

	KeInitializeCallbackRecord(&bugrecord);
	KeRegisterBugCheckCallback(&bugrecord,
		(PKBUGCHECK_CALLBACK_ROUTINE)BugcheckCallback,
		&bugbuffer,
		sizeof(bugbuffer),
		(PUCHAR) "BUGCHECK");

	// Cause a bug check

	KeBugCheckEx(0x1234, 0, 1, 2, 3);

	return STATUS_SUCCESS; // never return
}


#pragma LOCKEDCODE
VOID BugcheckCallback(PULONG buffer, ULONG bufsize)
{
	*buffer = 42;
}

