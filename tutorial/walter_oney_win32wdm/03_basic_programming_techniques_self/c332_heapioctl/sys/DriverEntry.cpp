

#include "Driver.h"
#include "Device.h"
#include "Ioctl.h"
#include "Power.h"

BOOLEAN win98 = FALSE;


#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDEVICE_OBJECT, PUNICODE_STRING RegistryPath)
{
	return STATUS_SUCCESS;
}

// #pragma LOCKEDCODE		// force inline functions into locked code
