/*
	c3_errstatus main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.2.2 Structured Exception Handling

	__try {
	}
	__finally {
	}

	__try {
	}
	__except(<filter_expression>) {
	}


	Cannot use try {} catch(...){}; It requires user-mode run-time library.

	Which exceptions can be trapped?
	At IRQL less than or equal to DISPATCH_LEVEL:	

	1) anything signaled by ExRaiseStatus and related functions
	2) dereference invalid pointer to user-mode memory
	3) debug/breakpoint exception
	4) integer overflow (INTO instruction)
	5) invalid opcode

	Cannot be trapped:
	1) dereference invalid kernel-mode pointer -> bug check (aka BSOD)
	2) divide by zero exception -> bug check (aka BSOD)
	3) BOUND instruction -> bug check (aka BSOD)

	Kernel-Mode Pointers
	1) cannot check them, always trust what kernel-mode component gives you
	2) always test pointers for NULL before using them

	Raising Exceptions:
	1)	Raise an exception only in a nonarbitrary thread context, when you know 
		there's an exception handler above you, and when you really know what you're doing.


00000015	4.17821646	C3_ERRSTATUS - Entering DriverEntry
00000016	4.17840528	C3_ERRSTATUS - Entering AddDevice: DriverObject 438B3060, pdo 43A84080
00000017	4.17840910	C3_ERRSTATUS - expected counter=0 to be 1?
00000018	4.17841196	C3_ERRSTATUS - Before ExRaiseAccessViolation()
00000019	4.17842436	C3_ERRSTATUS - inside __except(EXCEPTION_EXECUTE_HANDLER) after ExRaiseAccessViolation()
00000020	4.17842722	C3_ERRSTATUS - Before ProbeForWrite(p, 4, 4)
00000021	4.17843485	C3_ERRSTATUS - inside __except(EXCEPTION_EXECUTE_HANDLER) after ProbeForWrite(..)
00000022	4.17843866	C3_ERRSTATUS - program kept control after ProbeForWrite(..) exception
00000023	4.17844200	C3_ERRSTATUS - before EvaluateException(GetExceptionCode(), GetExceptionInformation())
00000024	4.17844772	C3_ERRSTATUS - inside EvaluateException(0xE6FC57C0, 0xE6FC5FF0)
00000025	4.17845392	C3_ERRSTATUS - inside __except after  EvaluateException(GetExceptionCode(), GetExceptionInformation())
00000026	4.17845678	C3_ERRSTATUS - before ProbeForRead(p1, 4, 4) with p1 invalid.
00000027	4.17846298	C3_ERRSTATUS - inside __except after  ProbeForRead(p1, 4, 4)
00000028	4.17857409	C3_ERRSTATUS - DriverUnload: DriverObject 438B3060

*/

#include "driver.h"



#define DRIVERNAME "C3_ERRSTATUS"

NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo);
VOID DriverUnload(PDRIVER_OBJECT DriverObject);
LONG EvaluateException(NTSTATUS, PEXCEPTION_POINTERS);

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint((DRIVERNAME " - Entering DriverEntry\n"));

	DriverObject->DriverExtension->AddDevice = AddDevice;
	DriverObject->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}


#pragma PAGEDCODE
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	/*
		1) keyword: __finally , clean up code that will always executed.
					__finally is like a catch( ) { ...; throw; }
					It does not stop stack unwinding, and instructions after closing 
					bracket	are not executed.
	*/
	LONG counter = 0;
	__try
	{
		++counter;
	}
	__finally
	{
		--counter;
	}
	KdPrint((DRIVERNAME " - expected counter=%d to be 1?\n", counter));



	/*
		2) keyword: __except(<filter_expression>)
					__except(EXCEPTION_EXECUTE_HANDLER) , ==1 stops stack unwinding and gives control
					__except(EXCEPTION_CONTINUE_SEARCH) , ==0 continues to search an upper exception frame
					__except(EXCEPTION_CONTINUE_EXECUTION),==-1 return to the point where exception was raised
	*/
	__try
	{
		KdPrint((DRIVERNAME " - Before ExRaiseAccessViolation()\n"));
		ExRaiseAccessViolation();
		KdPrint((DRIVERNAME " - After  ExRaiseAccessViolation() !!!!!!! Oh no!\n"));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - inside __except(EXCEPTION_EXECUTE_HANDLER) after ExRaiseAccessViolation()\n"));
	}

	PVOID p = (PVOID)1;
	__try
	{
		KdPrint((DRIVERNAME " - Before ProbeForWrite(p, 4, 4)\n"));
		ProbeForWrite(p, 4, 4);
		KdPrint((DRIVERNAME " - After  ProbeForWrite(p, 4, 4) !!!!!! Oh no!"));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - inside __except(EXCEPTION_EXECUTE_HANDLER) after ProbeForWrite(..)\n"));
	}

	KdPrint((DRIVERNAME " - program kept control after ProbeForWrite(..) exception\n"));


	/*
		3)	Note that you cannot trap arithmetic exceptions, or page faults due to 
			referencing an invalid kernel-mode pointer, by using structured exceptions. 
			You just have to write your code so as not to generate such exceptions. 
			It is pretty obvious how to avoid dividing by 0.
	*/

	ULONG numerator = 22, denominator = 0; // <== numbers someone gives you
	ULONG quotient;
	// quotient = numerator / denominator; -> BSOD!


	/*
		4)	GetExceptionCode(), GetExceptionInformation() are available only in
			__except clause filter expression.
	*/

	__try
	{
		KdPrint((DRIVERNAME " - before EvaluateException(GetExceptionCode(), GetExceptionInformation())\n"));
		ExRaiseAccessViolation();
	}
	__except (EvaluateException(GetExceptionCode(), GetExceptionInformation()))
	{
		KdPrint((DRIVERNAME " - inside __except after  EvaluateException(GetExceptionCode(), GetExceptionInformation())\n"));
	}

	
	/*
		5)	Real World Example with ProbeForRead(..)
			p is a pointer from user-mode untrusted source and we believe it may point
			to an integer, so we test it before use.
	*/
	PLONG p1 = (PLONG) 1; // from user-mode
	__try
	{
		KdPrint((DRIVERNAME " - before ProbeForRead(p1, 4, 4) with p1 invalid."));
		ProbeForRead(p1, 4, 4);
		LONG x = *p1;             // DANGEROUS!!!!!!!! but never reached.
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		NTSTATUS status = GetExceptionCode();
		KdPrint((DRIVERNAME " - inside __except after  ProbeForRead(p1, 4, 4)"));
	}


	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}


LONG EvaluateException(NTSTATUS status, PEXCEPTION_POINTERS excp)
{
	KdPrint((DRIVERNAME " - inside EvaluateException(0x%X, 0x%X)\n"), status, excp);
	return EXCEPTION_EXECUTE_HANDLER;
}