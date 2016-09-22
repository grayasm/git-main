/*
	Control.cpp -- IOCTL handlers for fputest driver
	Copyright (C) 1999 by Walter Oney
*/


#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"

/*	!!!!This sample is only appropriate for x86 targets!!!!	*/

#ifndef _X86_
#error The FPUTEST sample is only for the x86 platform

NTSTATUS DoTest(char* irql);

/*
	Whenever a C program uses floating point, the compiler generates a reference
	to the dummy symbol __fltused in order to drag in the runtime support. We
	don't want the standard support in a kernel-mode driver, however, so we
	satisfy the reference this way:
*/

extern "C" ULONG _fltused = 0;

/*
	Many floating point functions, including SIN and SQRT, are implemented by
	runtime library routines even though the x87 coprocessor has instructions
	for performing them. Since we can't link these routines into a driver, we
	need to supply intrinsic implementations for them, such as the following. Since
	these routines just use the native coprocessor instructions, they imply default
	error handling.
*/

inline double sin(double x)
{
	double result;

	_asm
	{
		fld x
		fsin
		fstp result
	}

	return result;
}

inline double sqrt(double x)
{
	double result;

	_asm
	{
		fld x
		fsqrt
		fstp result
	}

	return result;
}




#pragma PAGEDCODE
NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	ULONG info = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (code)
	{

	case IOCTL_TEST_PASSIVE: // code == 0x800
	{
		status = DoTest("PASSIVE_LEVEL");
		break;
	}

	case IOCTL_TEST_DISPATCH: // code == 0x801
	{
		KIRQL oldirql;
		KeRaiseIrql(DISPATCH_LEVEL, &oldirql);
		status = DoTest("DISPATCH_LEVEL");
		KeLowerIrql(oldirql);
		break;
	}

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
} // DispatchControl




#pragma LOCKEDCODE
NTSTATUS DoTest(char* irql)
{

	/*
		Before performing any floating point operations in a thread (other than
		a kernel mode thread we created by calling PsCreateSystemThread), save
		the non-volatile state of the coprocessor. This operation should also
		reinitialize the coprocessor. In Win98, however, the code is optimized
		in such a way that it may not actually do an FSAVE, so the initialization
		may not actually occur. It's better practice to perform our own FINIT and
		then load a control word containing whatever values we'd like, as shown
		here.
	*/

	KFLOATING_SAVE savearea;
	NTSTATUS status = KeSaveFloatingPointState(&savearea);
	if (!NT_SUCCESS(status))
	{
		KdPrint((DRIVERNAME " - KeSaveFloatingPointState failed - %X\n", status));
		return status;
	}

	/*
		Although we can use structured exceptions to catch floating point errors, the
		compiler may insert WAIT instructions at random places outside the scope of our
		__try blocks, leading to bug checks that we can't control. Rather than trying to
		work around this, it's just simpler to mask all floating point exceptions. That
		causes the FPU to perform its default fix up action for any error.
	*/

	USHORT cw = 0x03FF;			// round to nearest, 64-bit precision, all exceptions masked

	_asm
	{						// initialize FPU
		fninit
		fldcw cw
	}						// initialize FPU

	double foo = 1.0;

	foo = foo * foo + foo;

	foo = sqrt(-sin(foo));

	KdPrint((DRIVERNAME " - result of %s test is %8.8lX %8.8lX\n", irql, foo));

	// If MMX instructions are available on this processor, exercise a few of them.

	if (ExIsProcessorFeaturePresent(PF_MMX_INSTRUCTIONS_AVAILABLE))
	{						// perform MMX test
		static UCHAR opnd1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
		static UCHAR opnd2[8] = {8, 7, 6, 5, 4, 3, 2, 1};
		static UCHAR expect[8] = {8, 8, 8, 8, 8, 8, 8, 8};
		UCHAR result[8];

		_asm
		{
			movq mm0, opnd1		; load 8 8-bit values
			paddsb mm0, opnd2	; do 8 additions at once
			movq result, mm0	; save result
			emms				; end MMX stream
		}

		if (RtlCompareMemory(result, expect, 8) == 8)
			KdPrint((DRIVERNAME " - Test of MMX PADDSB instruction worked\n"));
		else
			KdPrint((DRIVERNAME " - Test of MMX PADDSB instruction failed - wrong result\n"));
	}						// perform MMX test
	else
		KdPrint((DRIVERNAME " - skipping MMX test because feature not available\n"));

	KeRestoreFloatingPointState(&savearea);
	return status;
} // DoTest

#endif // _X86_
