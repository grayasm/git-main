/*
	c3_basic main program.
	Copyright (C) 2016 by Mihai Vasilian

	This is the most basic, useless driver sample. Return false from AddDevice.

	00000010	3.13531065	[11860] SAMCLASS - DIF_ALLOW_INSTALL
	00000011	3.13783407	[11860] SAMCLASS - DIF_INSTALLDEVICEFILES
	00000012	3.16497278	[11860] SAMCLASS - DIF_REGISTER_COINSTALLERS
	00000013	3.16781068	[11860] SAMCLASS - DIF_INSTALLINTERFACES
	00000014	3.17019653	[11860] SAMCLASS - DIF_INSTALLDEVICE
	00000015	3.20354414	C3_NTSTRSAFE - Entering DriverEntry
	00000016	3.20361233	C3_NTSTRSAFE - Entering AddDevice: DriverObject 0988DCD0, pdo 04F55080
	00000017	3.20365262	C3_NTSTRSAFE - DriverUnload: DriverObject 0988DCD0
	00000018	3.20666265	[11860] SAMCLASS - DIF_NEWDEVICEWIZARD_FINISHINSTALL
	00000019	3.28054667	[11860] SAMCLASS - DIF_DESTROYPRIVATEDATA

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <wdm.h>

#ifdef __cplusplus
}
#endif


#define PAGEDCODE	code_seg("PAGE")
#define LOCKEDCODE	code_seg()
#define INITCODE	code_seg("INIT")

#define PAGEDDATA	data_seg("PAGEDATA")
#define LOCKEDDATA	data_seg()
#define INITDATA	data_seg("INITDATA")



#define DRIVERNAME "C3_NTSTRSAFE"

NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo);
VOID DriverUnload(PDRIVER_OBJECT DriverObject);

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
	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}


