+------------------------------------------------------------------------+
		Chapter 14 Building DLLs
+------------------------------------------------------------------------+
	The guidelines for producing DLLs that will be safe in a 
	multithreaded environment are straightforward:
	
	* Do not use global variables except for TLS slot storage.
	
	  The idea is that a global variable in a DLL is shared with all the
	  DLL threads running at any time in the same process.
	  If a global variable should have thread specific value only then you
	  should you TLS, otherwise it is ok to use the global one providing 
	  exclusive access for writing by use of a synchronization mechanism 
	  (e.g. mutex, sempahore, critical section, etc).
	  
	* Do not use static variables.
	  
	  Functions using local/global static variables will share the same value
	  across all threads.
	  
	* DO use thread local storage.
	* DO use your stack.
	
+------------------------------------------------------------------------+