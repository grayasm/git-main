+-------------------------------------+--------------------------------+
|  CRITICAL_SECTION                        MUTEX Kernel Object
+ ------------------------------------+--------------------------------+
|  InitializeCriticalSection()            CreateMutex()
|                                         OpenMutex()
+-------------------------------------+--------------------------------+
|  EnterCriticalSection()                 WaitForSingleObject()
|                                         WaitForMultipleObjects()
|                                         MsgWaitForMultipleObjects()
+-------------------------------------+--------------------------------+
|  LeaveCriticalSection()                 ReleaseMutex()
+-------------------------------------+--------------------------------+
|  DeleteCriticalSection()                CloseHandle()
+-------------------------------------+--------------------------------+

MUTEX/SEMAPHORE - the same


+-------------------------------------+--------------------------------+
|  CRITICAL_SECTION                        EVENT Kernel Object
+ ------------------------------------+--------------------------------+
|  InitializeCriticalSection()            CreateEvent()
|                                         OpenEvent()
+-------------------------------------+--------------------------------+
|  EnterCriticalSection()                 WaitForSingleObject()
|                                         WaitForMultipleObjects()
|                                         MsgWaitForMultipleObjects()
+-------------------------------------+--------------------------------+
|  LeaveCriticalSection()                 SetEvent()
|                                         PulseEvent()
|                                         ResetEvent()
+-------------------------------------+--------------------------------+
|  DeleteCriticalSection()                CloseHandle()
+-------------------------------------+--------------------------------+



+----------------------------------------------------------------------+
                Summary of Synchronization Mechanisms
+----------------------------------------------------------------------+
CRITICAL_SECTION
   Is a local object, not a kernel object.
   Is fast and efficient.
   Cannot be waited on more than one at a time.
   Cannot determine if it was abandoned by a thread.
   
MUTEX
   Is a kernel object.
   It is owned by only 1 thread at a time.
   Generates an "abandoned" error if the owning thread terminates.
   Can be used in WaitForSingleObject/similar calls.
   Is named, and can be opened across processes.
   Can only be released by the thread that owns it.
   
SEMAPHORE
   Is a kernel object.
   Has no owner.
   Allows a given maximum number of threads to run in paralel at any particular time.
   Can be used in WaitForSingleObject/similar calls.   
   Is named and can be opened across processes.
   Can be released by any thread.
   
   
EVENT
   Is a kernel object.
   Is completly under program control (SetEvent,ResetEvent).
   Is good for designing new synchronization objects.
   Does not queue up wake-up requests.
   Is named and can be opened across processes.
   
   
INTERLOCKED VARIABLE
   Allow basic operations on 4-byte values without having to use critical section or mutex.
   Work even in SMP systems.
+----------------------------------------------------------------------+   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   