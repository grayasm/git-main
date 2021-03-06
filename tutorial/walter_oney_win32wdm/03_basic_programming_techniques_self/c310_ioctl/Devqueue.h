/*
	Device Queue header file.
	Copyright (C) 1999, 2000 by Walter Oney.
*/


#ifndef __Devqueue_h__
#define __Devqueue_h__

#include "Driver.h"

typedef VOID(__stdcall *PQNOTIFYFUNC)(PVOID);

typedef struct _DEVQUEUE
{
	LIST_ENTRY		head;
	KSPIN_LOCK		lock;
	PDRIVER_STARTIO StartIo;
	LONG			stallcount;
	PIRP			CurrentIrp;
	KEVENT			evStop;
	PQNOTIFYFUNC	notify;
	PVOID			notifycontext;
	NTSTATUS		abortstatus;
} DEVQUEU, *PDEVQUEUE;


GENERICAPI VOID		GENERIC_EXPORT InitializeQueue(PDEVQUEUE pdq, PDRIVER_STARTIO StartIo);
GENERICAPI VOID		GENERIC_EXPORT StartPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo, PIRP Irp, PDRIVER_CANCEL cancel);
GENERICAPI PIRP		GENERIC_EXPORT StartNextPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo);
GENERICAPI VOID		GENERIC_EXPORT CancelRequest(PDEVQUEUE pdq, PIRP Irp);
GENERICAPI VOID		GENERIC_EXPORT CleanupRequests(PDEVQUEUE pdq, PFILE_OBJECT fop, NTSTATUS status);
GENERICAPI VOID		GENERIC_EXPORT StallRequests(PDEVQUEUE pdq);
GENERICAPI VOID		GENERIC_EXPORT RestartRequests(PDEVQUEUE pdq, PDEVICE_OBJECT fdo);
GENERICAPI PIRP		GENERIC_EXPORT GetCurrentIrp(PDEVQUEUE pdq);
GENERICAPI BOOLEAN	GENERIC_EXPORT CheckBusyAndStall(PDEVQUEUE pdq);
GENERICAPI VOID		GENERIC_EXPORT WaitForCurrentIrp(PDEVQUEUE pdq);
GENERICAPI VOID		GENERIC_EXPORT AbortRequests(PDEVQUEUE pdq, NTSTATUS status);
GENERICAPI VOID		GENERIC_EXPORT AllowRequests(PDEVQUEUE pdq);
GENERICAPI NTSTATUS	GENERIC_EXPORT AreRequestsBeingAborted(PDEVQUEUE pdq);
GENERICAPI NTSTATUS	GENERIC_EXPORT StallRequestsAndNotify(PDEVQUEUE pdq, PQNOTIFYFUNC notify, PVOID context);



/*	Multiple queue routines added in version 1.3:	*/

GENERICAPI VOID		GENERIC_EXPORT CleanupAllRequests(PDEVQUEUE* q, ULONG nq, PFILE_OBJECT fop, NTSTATUS status);
GENERICAPI VOID		GENERIC_EXPORT StallAllRequests(PDEVQUEUE* q, ULONG nq);
GENERICAPI VOID		GENERIC_EXPORT RestartAllRequests(PDEVQUEUE* q, ULONG nq, PDEVICE_OBJECT fdo);
GENERICAPI BOOLEAN	GENERIC_EXPORT CheckAnyBusyAndStall(PDEVQUEUE* q, ULONG nq, PDEVICE_OBJECT fdo);
GENERICAPI VOID		GENERIC_EXPORT WaitForCurrentIrps(PDEVQUEUE* q, ULONG nq);
GENERICAPI VOID		GENERIC_EXPORT AbortAllRequests(PDEVQUEUE* q, ULONG nq, NTSTATUS status);
GENERICAPI VOID		GENERIC_EXPORT AllowAllRequests(PDEVQUEUE* q, ULONG nq);
GENERICAPI NTSTATUS	GENERIC_EXPORT StallAllRequestsAndNotify(PDEVQUEUE* q, ULONG nq, PQNOTIFYFUNC notify, PVOID context);


typedef struct _NOTIFY_CONTEXT
{
	PQNOTIFYFUNC notify;			// real notification function
	PVOID context;					// context arg for notification function
	LONG count;						// number of busy queues
} NOTIFY_CONTEXT, *PNOTIFY_CONTEXT;

VOID NotificationCallback(PNOTIFY_CONTEXT ctx);




#endif // __Devqueue_h__
