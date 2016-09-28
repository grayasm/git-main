/*
	Remove Lock header file.
	Copyright (C) 1999, 2000 by Walter Oney.
*/


#ifndef __RemoveLock_h__
#define __RemoveLock_h__


#include "Driver.h"




/*	The support routines for remove locking were not originally declared
in WDM.H because they weren't implemented in Win98 Gold.
The following declarations provide equivalent functionality on all
WDM platforms.
*/

typedef struct _GENERIC_REMOVE_LOCK
{
	LONG usage;				// reference count
	BOOLEAN removing;		// true if removal is pending
	KEVENT evRemove;		// event to wait on
} GENERIC_REMOVE_LOCK, *PGENERIC_REMOVE_LOCK;


GENERICAPI VOID		GENERIC_EXPORT GenericInitializeRemoveLock(PGENERIC_REMOVE_LOCK lock, ULONG tag, ULONG minutes, ULONG maxcount);
GENERICAPI NTSTATUS	GENERIC_EXPORT GenericAcquireRemoveLock(PGENERIC_REMOVE_LOCK lock, PVOID tag);
GENERICAPI VOID		GENERIC_EXPORT GenericReleaseRemoveLock(PGENERIC_REMOVE_LOCK lock, PVOID tag);
GENERICAPI VOID		GENERIC_EXPORT GenericReleaseRemoveLockAndWait(PGENERIC_REMOVE_LOCK lock, PVOID tag);



/*	NTDDK.H and WDM.H declares the documented support functions as
macros which we need to redefine.
*/

#if !defined(_NTDDK_)
#error You must include WDM.H or NTDDK.H before GENERIC.H
#endif

#undef IoInitializeRemoveLock
#define IoInitializeRemoveLock GenericInitializeRemoveLock

#undef IoAcquireRemoveLock
#define IoAcquireRemoveLock GenericAcquireRemoveLock

#undef IoReleaseRemoveLock
#define IoReleaseRemoveLock GenericReleaseRemoveLock

#undef IoReleaseRemoveLockAndWait
#define IoReleaseRemoveLockAndWait GenericReleaseRemoveLockAndWait



/*	NTDDK.H/WDM.H declares an IO_REMOVE_LOCK structure.	*/

#define _IO_REMOVE_LOCK _GENERIC_REMOVE_LOCK
#define IO_REMOVE_LOCK GENERIC_REMOVE_LOCK
#define PIO_REMOVE_LOCK PGENERIC_REMOVE_LOCK






#endif // __RemoveLock_h__