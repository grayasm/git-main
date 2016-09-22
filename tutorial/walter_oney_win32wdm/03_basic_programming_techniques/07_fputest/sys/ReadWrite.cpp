/*
	Read/Write request processors for fputest driver
	Copyright (C) 1999 by Walter Oney
*/


#include "stddcls.h"
#include "driver.h"



#pragma PAGEDCODE
NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - IRP_MJ_CREATE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	NTSTATUS status = STATUS_SUCCESS;
	InterlockedIncrement(&pdx->handles);
	return CompleteRequest(Irp, status, 0);
}




#pragma PAGEDCODE
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - IRP_MJ_CLOSE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	InterlockedDecrement(&pdx->handles);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
}



#pragma PAGEDCODE
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
{
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	return STATUS_SUCCESS;
}



#pragma PAGEDCODE
VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
{
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
}
