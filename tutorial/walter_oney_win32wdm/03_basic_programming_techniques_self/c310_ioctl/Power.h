/*
	Power header file.
	Copyright (C) 1999, 2000 by Walter Oney.
*/


#ifndef __Power_h__
#define __Power_h__


#include "Driver.h"
#include "Device.h"
#include "Ioctl.h"
#include "Pnp.h"



#ifndef CTL_CODE
#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif


/*	IOCTL interface for generic power management.	*/

#define IOCTL_GET_POWERINFO	CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_POWERINFO CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IDLENOW		CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF2, METHOD_NEITHER,  FILE_ANY_ACCESS)


typedef struct _POWERINFO
{
	unsigned long ulConservation;	// idle timeout in conservation mode
	unsigned long ulPerformance;	// idle timeout in performance mode
	unsigned char bWakeup;			// TRUE if wakeup feature should be armed
	unsigned char bCanWake;			// device capable of waking system
	unsigned char bCanIdle;			// device can be idled
	unsigned char bIdle;			// device is idle right now
} POWERINFO, *PPOWERINFO;


enum POWSTATE
{
	InitialState = 0,				// initial state of FSM
	SysPowerUpPending,				// system power-up IRP forwarded
	SubPowerUpPending,				// waiting for nested device power up to finish
	SubPowerDownPending,			// waiting from device to power down before forwarding system power-down IRP
	SysPowerDownPending,			// waiting for system power-down IRP to finish
	DevPowerUpPending,				// waiting for device power-up IRP
	DevPowerDownPending,			// waiting for device power-down IRP
	ContextSavePending,				// context save is underway
	ContextRestorePending,			// context restore is underway
	DevQueryUpPending,				// device query for power-up pending
	DevQueryDownPending,			// device query for power-down pending
	QueueStallPending,				// waiting for device to be idle
	SaveSeqPending,					// waiting to get sequence numbers after context save
	RestoreSeqPending,				// waiting to get sequence numbers before context restore
	PassiveCompletePending,			// waiting for PASSIVE_LEVEL callback to complete IRP
	FinalState,						// final state of FSM
	NUMPOWSTATES

};

enum POWEVENT
{
	NewIrp = 0,						// new query/set IRP
	MainIrpComplete,				// the main IRP has finished
	AsyncNotify,					// some other event has occurred
	NUMPOWEVENTS

};

typedef struct _POWCONTEXT
{
	LONG				id;				// unique sequence number for this IRP
	LONG				eventcount;		// number of events generated for this IRP
	PGENERIC_EXTENSION	pdx;			// our own device extension
	PIRP				irp;			// the IRP we're processing
	enum POWSTATE		state;			// current state of FSM
	NTSTATUS			status;			// completion status for main IRP
	DEVICE_POWER_STATE	devstate;		// device power state to use
	POWER_SEQUENCE		sequence;		// sequence numbers retrieved by ditto
	DEVICE_POWER_STATE	oldpower;		// previous device power state
	UCHAR				MinorFunction;	// minor function to use in requested power IRP
	BOOLEAN				UnstallQueue;	// unstall queue when main IRP finishes
} POWCONTEXT, *PPOWCONTEXT;


NTSTATUS HandlePowerEvent(PPOWCONTEXT ctx, enum POWEVENT event);



/*	Devices that use GENERIC.SYS for power management register an interface
with the following GUID:

{894A7461-A033-11d2-821E-444553540000}
*/
#include <InitGuid.h>
DEFINE_GUID(GUID_GENERIC_POWER, 0x894a7461, 0xa033, 0x11d2, 0x82, 0x1e, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);


VOID AdjustSpecialFileCounter(PGENERIC_EXTENSION pdx, BOOLEAN inpath, PLONG counter);
NTSTATUS GetPowerInfoFromRegistry(PGENERIC_EXTENSION pdx, PPOWERINFO pip);
NTSTATUS ImplementPowerPolicy(PGENERIC_EXTENSION pdx, PPOWERINFO pip);
BOOLEAN OkayToRemove(PGENERIC_EXTENSION pdx);
BOOLEAN OkayToStop(PGENERIC_EXTENSION pdx);
NTSTATUS SendDeviceSetPower(PGENERIC_EXTENSION pdx, DEVICE_POWER_STATE state, BOOLEAN wait = FALSE);
NTSTATUS WritePowerInfoToRegistry(PGENERIC_EXTENSION pdx, PPOWERINFO pip);


GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPower(PGENERIC_EXTENSION, PIRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericHandlePowerIoctl(PGENERIC_EXTENSION pdx, PIRP Irp);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericIdleDevice(PGENERIC_EXTENSION pdx, DEVICE_POWER_STATE state, BOOLEAN wait = FALSE);
GENERICAPI VOID		GENERIC_EXPORT GenericMarkDeviceBusy(PGENERIC_EXTENSION);
GENERICAPI VOID		GENERIC_EXPORT GenericRegisterForIdleDetection(PGENERIC_EXTENSION, ULONG ConservationTimeout, ULONG PerformanceTimeout, DEVICE_POWER_STATE State);
GENERICAPI VOID		GENERIC_EXPORT GenericSaveRestoreComplete(PVOID context);
GENERICAPI NTSTATUS	GENERIC_EXPORT GenericWakeupControl(PGENERIC_EXTENSION pdx, enum WAKEFUNCTION wf);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupFromIdle(PGENERIC_EXTENSION pdx, BOOLEAN wait = FALSE);


NTSTATUS MainCompletionRoutine(PDEVICE_OBJECT junk, PIRP Irp, PPOWCONTEXT ctx);
NTSTATUS SequenceCompletionRoutine(PDEVICE_OBJECT junk, PIRP Irp, PPOWCONTEXT ctx);
VOID PoCompletionRoutine(PDEVICE_OBJECT junk, UCHAR fcn, POWER_STATE state, PPOWCONTEXT ctx, PIO_STATUS_BLOCK pstatus);
NTSTATUS SafePoCallDriver(PDEVICE_OBJECT DeviceObject, PIRP Irp);
VOID PassivePowerComplete(PPOWCONTEXT ctx);


#endif // __Power_h__
