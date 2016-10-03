/*
	DriverEntry.cpp - Main program for sehtest sample driver.
	Copyright (C) 1999 by Walter Oney
*/


#include "stddcls.h"


#define DRIVERNAME "SEHTEST"


extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint((DRIVERNAME " - Entering DriverEntry\n"));

	BOOLEAN win9x = !IoIsWdmVersionAvailable(1, 0x10);

	PVOID p = (PVOID)1;

	/*	Exception raised by ProbeForWrite on misaligned address.	*/
	__try
	{
		KdPrint((DRIVERNAME " - About to generate alignment exception in ProbeForWrite\n"));

		ProbeForWrite(p, 4, 4);

		KdPrint((DRIVERNAME " - You shouldn't see this message\n"));

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - Exception was caught - %X\n", GetExceptionCode()));
	}

	/*	Exception due to user-mode pointer dereference.	*/

	if (win9x)
		p = (PVOID)0x01000000;
	__try
	{
		KdPrint((DRIVERNAME " - About to generate page fault\n"));

		int x = *(int*)p;

		KdPrint((DRIVERNAME " - You shouldn't see this message\n"));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - Exception was caught - %X\n", GetExceptionCode()));
	}


	// Debug exception

#ifdef _X86_

	__try
	{
		KdPrint((DRIVERNAME " - About to generate debug exception\n"));
		_asm pushfd
		_asm or dword ptr[esp], 100h; trap flag
		_asm popfd
		_asm test eax, eax
		KdPrint((DRIVERNAME " - You shouldn't see this message\n"));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - Exception was caught - %X\n", GetExceptionCode()));
	}

	// Breakpoint exception

	__try
	{
		KdPrint((DRIVERNAME " - About to generate breakpoint exception\n"));
		_asm int 3
		KdPrint((DRIVERNAME " - You shouldn't see this message\n"));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - Exception was caught - %X\n", GetExceptionCode()));
	}

	// Overflow exception

	__try
	{
		KdPrint((DRIVERNAME " - About to generate overflow exception\n"));
		_asm mov eax, 0x80000000
		_asm add eax, 0x80000000
		_asm into
		KdPrint((DRIVERNAME " - You shouldn't see this message\n"));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - Exception was caught - %X\n", GetExceptionCode()));
	}

#endif // _X86_

	// Enough!!

	KdPrint((DRIVERNAME " - Program kept control after exceptions\n"));

	__try
	{
		return STATUS_UNSUCCESSFUL;
	}
	__finally
	{
		KdPrint((DRIVERNAME " - Failing DriverEntry; cleanup handler got control first\n"));
	}

	KdPrint((DRIVERNAME " - You shouldn't see this message\n"));
	
	return STATUS_SUCCESS; // never reached
} // DriverEntry