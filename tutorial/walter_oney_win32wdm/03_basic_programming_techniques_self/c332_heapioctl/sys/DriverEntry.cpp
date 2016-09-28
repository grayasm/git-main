/*
	DriverEntry.cpp - driver entry function.
	Copyright (C) 1999, 2000 by Walter Oney.
*/



#include "Driver.h"
#include "Device.h"
#include "Ioctl.h"
#include "Power.h"


#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDEVICE_OBJECT, PUNICODE_STRING RegistryPath)
{
	return STATUS_SUCCESS;
}

#pragma LOCKEDCODE		// force inline functions into locked code
