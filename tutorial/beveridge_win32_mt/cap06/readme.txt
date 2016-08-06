+------------------------------------------------+
   Overalpped I/O usage techniques
+------------------------------------------------+
   Signaled File Handles
   Signaled Event Objects
   Asynchronous Procedure Calls (APCs)
   I/O  Completion Ports
+================================================+
   Signaled File Handles
+------------------------------------------------+
   struct OVERLAPPED
   CreateFile()
   ReadFile() / WriteFile()
   WaitForSingleObject()
   GetOveralppedResult()
   CloseHandle()   

+================================================+
   Signaled Event Objects
+------------------------------------------------+
   CreateFile()
   CreateEvent()
   ReadFile() / WriteFile()
   WaitForMultipleObjects()
   GetOverlappedResult()
   CloseHandle()
   
+================================================+
   Asynchronous Procedure Calls (APCs)
+------------------------------------------------+
   CreateFile()
   CreateEvent()
   ReadFileEx() / WriteFileEx()
   FileIOCompletionRoutine() -> SetEvent()
   WaitForSingleObjectEx()
   CloseHandle()
+------------------------------------------------+