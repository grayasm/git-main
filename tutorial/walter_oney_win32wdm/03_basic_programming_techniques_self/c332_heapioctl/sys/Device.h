#ifndef __Device_h__
#define __Device_h__

#include "Driver.h"
#include "RemoveLock.h"
#include "Devqueue.h"
#include "Device.h"





typedef NTSTATUS	(__stdcall *PSTART_DEVICE)(PDEVICE_OBJECT, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated);
typedef VOID		(__stdcall *PSTOP_DEVICE)(PDEVICE_OBJECT, BOOLEAN);
typedef VOID		(__stdcall *PREMOVE_DEVICE)(PDEVICE_OBJECT);
typedef BOOLEAN		(__stdcall *PQUERYFUNCTION)(PDEVICE_OBJECT);
typedef BOOLEAN		(__stdcall *PQUERYPOWERFUNCTION)(PDEVICE_OBJECT, DEVICE_POWER_STATE, DEVICE_POWER_STATE);
typedef VOID		(__stdcall *PCONTEXTFUNCTION)(PDEVICE_OBJECT, DEVICE_POWER_STATE, DEVICE_POWER_STATE, PVOID);
typedef VOID		(__stdcall *PFLUSHIOFUNCTION)(PDEVICE_OBJECT, UCHAR, UCHAR, DEVICE_POWER_STATE, DEVICE_POWER_STATE);
typedef DEVICE_POWER_STATE(__stdcall *PGETDSTATEFUNCTION)(PDEVICE_OBJECT, SYSTEM_POWER_STATE, DEVICE_POWER_STATE);



/* Device extension structure. */
enum DEVSTATE
{
	STOPPED,				// device stopped
	WORKING,				// started and working
	PENDINGSTOP,			// stop pending
	PENDINGREMOVE,			// remove pending
	SURPRISEREMOVED,		// removed by surprise
	REMOVED					// removed
};


typedef struct _GENERIC_EXTENSION
{
	PDEVICE_OBJECT			DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT			LowerDeviceObject;		// next lower driver in same stack
	PDEVICE_OBJECT			Pdo;					// the PDO
	PGENERIC_REMOVE_LOCK	RemoveLock;				// removal control locking structure
	DEVSTATE				state;					// current state of device
	DEVSTATE				prevstate;				// state prior to removal query
	DEVICE_POWER_STATE		devpower;				// current device power state
	SYSTEM_POWER_STATE		syspower;				// current system power state
	PULONG					idlecount;				// address of idle counter from idle detection registration
	ULONG					cto;					// conservation timeout
	ULONG					pto;					// performance timeout
	DEVICE_POWER_STATE		idlestate;				// idle state requested by minidriver
	DEVICE_CAPABILITIES		devcaps;				//copy of most recent device capabilities
	ULONG					nqueues;				// number of queues
	PDEVQUEUE*				queues;					// IRP queues
	PSTART_DEVICE			StartDevice;			// routine to initialize device configuration
	PSTOP_DEVICE			StopDevice;				// routine to release device configuration
	PREMOVE_DEVICE			RemoveDevice;			// routine to remove device object
	PQUERYFUNCTION			OkayToStop;				// okay to stop device now?
	PQUERYFUNCTION			OkayToRemove;			// okay to remove device now?
	PFLUSHIOFUNCTION		FlushPendingIo;			// encourage pending I/O to finish
	PGETDSTATEFUNCTION		GetDevicePowerState;	// get D-state for given S-state
	CHAR					DebugName[64];			// name for debugging messages
	ULONG					Flags;					// flags from initialization call
	LONG					npagefiles;				// # page files about which we've been notified
	LONG					ndumpfiles;				// # dump ditto
	LONG					nhibernatefiles;		// # hibernate ditto
	LIST_ENTRY				PendingIoctlList;		// list of asynchronous IOCTLs
	KSPIN_LOCK				IoctlListLock;			// lock for pending IOCTLs
	NTSTATUS				IoctlAbortStatus;		// abort incoming IOCTLs if nonzero
	PQUERYPOWERFUNCTION		QueryPower;				// okay to change device power?
	PCONTEXTFUNCTION		SaveDeviceContext;		// routine to save device context
	PCONTEXTFUNCTION		RestoreDeviceContext;	// routine to restore device context
	PNP_DEVICE_STATE		pnpstate;				// new PnP state bits
	PNP_DEVICE_STATE		pnpstatemask;			// mask of changed state bits
	DEVICE_POWER_STATE		PerfBoundary;			// context restore very expensive from >= this power state
	PIRP					WaitWakeIrp;			// outstanding WAIT_WAKE request (if any)
	LONG					wwcancelled;			// non-zero when WAIT_WAKE has been cancelled
	LONG					wwoutstanding;			// non-zero between PoReqeustPowerIrp and WaitWaitCallback
	POWER_SEQUENCE			oldseq;					// old power sequence numbers
	KEVENT					iflock;					// for interlocking use of interface list
	LIST_ENTRY				iflist;					// list of registered device interfaces
	KEVENT					evPagingPath;			// synchronization event used as a mutex for paging path notifications
	BOOLEAN					HardwareWorking;		// we should touch hardware at stop-device time
	BOOLEAN					WakeupEnabled;			// device wakeup feature is enabled
	BOOLEAN					StalledForPower;		// power management has stalled IRP queue
	BOOLEAN					GotCapabilities;		// capabilities have been gotten already
} GENERIC_EXTENSION, *PGENERIC_EXTENSION;


typedef struct _INTERFACE_RECORD
{
	LIST_ENTRY				list;					// linking fields
	GUID					guid;					// guid for registered interface
	UNICODE_STRING			linkname;				// symbolic link name
	BOOLEAN					enabled;				// true if interface currently enabled
} INTERFACE_RECORD, *PINTERFACE_RECORD;



NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status, ULONG_PTR info);
NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status);
NTSTATUS ForwardAndWait(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS OnRequestComplete(PDEVICE_OBJECT junk, PIRP Irp, PKEVENT pev);


struct QSIO
{
	PDEVQUEUE				DeviceQueue;
	PDRIVER_STARTIO			StartIo;
};


typedef struct _GENERIC_INIT_STRUCT
{
	ULONG					Size;					// Size of this structure.
	PDEVICE_OBJECT			DeviceObject;			// The device object being registered.
	PDEVICE_OBJECT			Pdo;					// The PDO below this device object.
	PDEVICE_OBJECT			Ldo;					// Immediately lower device object.
	PGENERIC_REMOVE_LOCK	RemoveLock;				// Address of remove lock in containing device extension (optional).
	PDEVQUEUE				DeviceQueue;			// Address of queue object for read/write IRPs (optional).
	PDRIVER_STARTIO			StartIo;				// Start I/O routine for reads & writes (required only if DeviceQueue non-NULL).
	PSTART_DEVICE			StartDevice;			// Routine to initialize device configuration.
	PSTOP_DEVICE			StopDevice;				// Routine to release device configuration.
	PREMOVE_DEVICE			RemoveDevice;			// Routine to remove device object.
	UNICODE_STRING			DebugName;				// Name to use in debug messages.
	ULONG					Flags;					// Option flags.
	PQUERYFUNCTION			OkayToStop;				// Routine to decide whether it's okay to stop device now (optional).
	PQUERYFUNCTION			OkayToRemove;			// Routine to decide whether it's okay to remove device now (optional).
	PQUERYPOWERFUNCTION		QueryPower;				// Routine to decide whether a proposed device power change is okay (optional).
	PCONTEXTFUNCTION		SaveDeviceContext;		// Routine to save device context before power down (optional).
	PCONTEXTFUNCTION		RestoreDeviceContext;	// Routine to restore device context after power up (optional).
	DEVICE_POWER_STATE		PerfBoundary;			// Power state below which context restore inordinately expensive (optional).
	ULONG					NumberOfQueues;			// Number of queues in DeviceQueues array (1.3)
	PFLUSHIOFUNCTION		FlushPendingIo;			// Encourage pending I/O to finish (optional) (2.0)
	PGETDSTATEFUNCTION		GetDevicePowerState;	// Get D-state for given S-State (optional) (1.10)
	ULONG					Reserved[6];			// Reserved for future use (1.3)
	struct QSIO				Queues[1];				// NumberOfQueues pointers to DEVQUEUE objects and their corresponding StartIo functions.

} GENERIC_INIT_STRUCT, *PGENERIC_INIT_STRUCT;





#endif // __Device_h__
