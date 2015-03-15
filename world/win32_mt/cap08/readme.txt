+---------------------------------------------------------------------------+
	Using C Run-time Library
+---------------------------------------------------------------------------+
	You should always use the multithreaded C run-time library, along
	with _beginthreadex() & _endthreadex(), if any thread other than
	the primary thread does any of the following:

	1) Uses malloc() or free() in C, or new or delete in C++

	2) Calls anything in stdio.h or io.h
		This includes fucntions such as fopen() and open(), getchar()
		write() and printf(). All of these functions use shared data
		structures as well as errno.

	3) Uses floating point variables or functions

	4) Calls any run-time functions that use a static buffer, such as
		asctime() strtok() rand()
		
		
	In order to be thread-safe the run-time C library must do some
	bookkeeping for each thread that starts up and shuts down. Without
	this bookkeeping, the run-time library would not know to allocate
	a new block of thread-local data for each new thread. Therefore
	there is a wrapper for CreateThread() called _beginthreadex() that
	takes care of additional bookkeeping.
	
	C run-time library time passed as flag to CL.exe compile:
	/ML		Single-Threaded
	/MT		Multithreaded
	/MD		Multithreaded DLL
	/MLd	Debug Single-Threaded
	/MTd	Debug Multithreaded
	/MDd	Debug Multithreaded DLL
+---------------------------------------------------------------------------+