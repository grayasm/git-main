+-----------------------------------------------------------------------------------------+
	WM_COPYDATA
	struct COPYDATASTRUCT
	SendMessage()
+-----------------------------------------------------------------------------------------+
	CreateFileMapping()
	OpenFileMapping()
	MapViewOfFile()
	UnmapViewOfFile()
	CloseHandle()
+-----------------------------------------------------------------------------------------+
	Anonymous Pipes		- MSDN: CreatePipe()
	Named Pipes			- MSDN: CreateNamedPipe()
	Mailslots			- MSDN: CreateMailslot()
	OLE Automation
	DDE
+=========================================================================================+
	Summary of using Shared Memory
+-----------------------------------------------------------------------------------------+
	If you are starting to get the idea that using shared memory is not simple, you are
	absolutely right. To implement a structure such as a linked list in shared memory,
	it would be necessary to build a custom memory allocator that can treat the shared
	memory region as a heap and returned based pointers withing that heap.
	This is not a trivial undertaking. The difficulty highlights the importance of keeping
	information sharing between threads to a minimum, and to tightly defined the interface
	through which any data is shared.
	
	Here are some guidelines for using shared memory:
	* Do not put C++ collection classes in shared memory
	* Never put C++ classes with virtual functions in shared memory
	* Never place MFC objects in shared memory that are based on CObject.
	* Do not use pointers that point within the shared memory area.
	* Do not use pointers that point outside the shared memory area.
	* It is safe to use "based" pointers but they should be used with care.
+=========================================================================================+