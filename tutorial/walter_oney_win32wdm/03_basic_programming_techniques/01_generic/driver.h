#ifndef __driver_h__
#define __driver_h__


#define GENERIC_INTERNAL
#include "generic.h"


/*	Remove the comment from the following line in order to build a version of
	GENERIC that works correctly on the first release of Win98. (There is a bug
	in this release such that the first call to a DllInitialize routine results
	in an error that prevents the driver from loading.) You will also need to modify
	the .DEF file to remove the export declarations for DllInitialize and DllUnload
*/
//#define WIN98SAFE

#define DRIVERNAME "GENERIC"    // for use in messages


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
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT LowerDeviceObject;		// next lower driver in same stack
	PDEVICE_OBJECT Pdo;						// the PDO
	PGENERIC_REMOVE_LOCK RemoveLock;		// removal control locking structure
	DEVSTATE state;							// current state of device
	DEVSTATE prevstate;						// state prior to removal query
	DEVICE_POWER_STATE devpower;			// current device power state
	SYSTEM_POWER_STATE syspower;			// current system power state
	PULONG idlecount;						// address of idle counter from idle detection registration
	ULONG cto;								// conservation timeout
	ULONG pto;
	DEVICE_POWER_STATE idlesate;
	DEVICE_CAPABILITIES devcaps;
	ULONG nqueues;
	PDEVQUEUE* queues;
	PSTART_DEVICE StartDevice;
	PSTOP_DEVICE StopDevice;
	PREMOVE_DEVICE RemoveDevice;
	PQUERYFUNCTION OkayToStop;
	PQUERYFUNCTION OkayToRemove;
	PFLUSHIOFUNCTION FlushPendingIo;
	PGETDSTATEFUNCTION GetDevicePowerState;
	CHAR DebugName[64];
	ULONG Flags;
	LONG npagefiles;
	LONG ndumpfiles;
	LONG nhibernatefiles;
	LIST_ENTRY PendingIoctlList;
	KSPIN_LOCK IoctlListLock;
	NTSTATUS IoctlAbortStatus;
	PQUERYPOWERFUNCTION QueryPower;
	PCONTEXTFUNCTION SaveDeviceContext;
	PCONTEXTFUNCTION RestoreDeviceContext;
	PNP_DEVICE_STATE pnpstatemask;
	DEVICE_POWER_STATE PerfBoundary;
	PIRP WaitWakeIrp;
	LONG wwcancelled;
	LONG wwoutstanding;
	POWER_SEQUENCE oldseq;
	KEVENT iflock;
	LIST_ENTRY iflist;
	KEVENT evPagingPath;
	BOOLEAN HardwareWorking;
	BOOLEAN WakeupEnabled;
	BOOLEAN StalledForPower;
	BOOLEAN GotCapabilities;
} GENERIC_EXTENSION;





#endif // __driver_h__
