/*
 * FileMapping.c  - Setting up and using a Shared Memory Area
 * 
 * CreateFileMapping()	- to create a shared memory area (on disk or in memory)
 * MapViewOfFile()		- maps the memory are into current process address space
 *						and returns a pointer to memory (can mount the whole file/memory
 *						or a truncated area of it)
 *						this memory should not contain pointers because their addresses
 *						are valid offsets from the base address of the process they've been
 *						created in, and are invalid in another processes.
 *
 * OpenFileMapping()	- in a child process to open a mapped file that alread exists
 * UnmapViewOfFile()	- to relase the shared memory area in the current process
 * CloseHandle()		- to release the kernel object
 *
 * If the file is mapped in multiple processes with read&write access, any change to 
 * the memory is available in all other processes.
 * In this sample I used a Mutex to synchronize write access to the shared memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


#define MAX_THREADS	6
#define BUF_SIZE 256
// Can use Global\  or Local\  to specify the location in system name space.
TCHAR	szFileName[] =	TEXT("Global\\MyFileMappingObject");
TCHAR	szMutexName[]=  TEXT("Global\\MyMutex");

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE		hMapFile;
	LPTSTR		pBuf;
	TCHAR		szMsg[] = TEXT("Message from first process");
	HANDLE		hThrds[MAX_THREADS];
	HANDLE		hMutex;
	int			i;
	DWORD		rc;	

	// Create File Mapped in Memory (shared memory accessible with pBuf pointer)
	hMapFile = CreateFileMapping(
						INVALID_HANDLE_VALUE,			// mapped in memory
						NULL,							// security
						PAGE_READWRITE,					// protection
						0,								// maxim object size
						BUF_SIZE,						// buffer size
						szFileName);					// kernel object name
	
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("\n\tShared area already initialized by another process");
		// we get however a valid handle to the object
	}
	MTVERIFY( hMapFile );

	// Get pointer to memory. In each other PROCESS this pointer will have a different value.
	MTVERIFY( pBuf = (LPTSTR) MapViewOfFile(
								hMapFile,				// object handle
								FILE_MAP_ALL_ACCESS,	// desired access
								0,						// high offset to truncate the view
								0,						// low offset to truncate the view
								BUF_SIZE));				// bytes to map

	/* shared memory should not contain pointers, because this shared memory
	   will be mounted at a different base address in each process that requests it
	 */
	strncpy(pBuf, szMsg, sizeof(szMsg));

	// synchronize access to memory
	MTVERIFY( hMutex = CreateMutex(
						NULL,
						FALSE,
						szMutexName) );


	for(i=0; i < MAX_THREADS; ++i)
	{
		MTVERIFY( hThrds[i] = CreateThread(
									NULL,
									0,
									ThreadFunc,
									(LPVOID)i,
									0,
									NULL));


		printf("\n\tLaunched thread %d", i);
	}


	rc = WaitForMultipleObjects(
				MAX_THREADS,
				hThrds, 
				TRUE,
				INFINITE);
	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + MAX_THREADS);

	for(i=0; i < MAX_THREADS; ++i)
		MTVERIFY( CloseHandle(hThrds[i]) );


	/* Without re-mapping again the file view, this memory is updated properly.
	 */
	printf("\n\tAll threads exited, pBuf= %s", pBuf);
	
	// Cleaning File Mapping 
	MTVERIFY( UnmapViewOfFile(pBuf) );
	MTVERIFY( CloseHandle(hMapFile) );
	

	printf("\n\tMain thread exit\n\n");

	return EXIT_SUCCESS;							
} // main


DWORD WINAPI ThreadFunc(LPVOID n)
{
	HANDLE		hMapFile;
	LPTSTR		pBuf;
	TCHAR		szMsg[BUF_SIZE];
	HANDLE		hMutex;
	int i;
	DWORD rc;


	// synchronize access to shared memory
	MTVERIFY( hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, szMutexName) );
	MTVERIFY( (rc = WaitForSingleObject(hMutex, INFINITE)) == WAIT_OBJECT_0 );


	/* client PROCESSES (here a thread only) should use OpenFileMapping
	 * which returns a handle to a file-mapping kernel object previously
	 * created by CreateFileMapping()
	 */
	MTVERIFY( hMapFile = OpenFileMapping(
								FILE_MAP_ALL_ACCESS,	// read/write access
								FALSE,					// do not inherit the name
								szFileName));			// name of mapping object


	/* This pointer has a different offset in each other PROCESS that maps the memory. */
	MTVERIFY( pBuf = (LPTSTR) MapViewOfFile(
								hMapFile,				// object handle
								FILE_MAP_ALL_ACCESS,	// read/write access
								0,						// high offset to truncate the view
								0,						// low offset to truncate the view
								BUF_SIZE));				// bytes to map

		
	printf("\n\tThread %d, pBuf= %s", n, pBuf);

	sprintf(szMsg, "%d%d%d%d%d%d%d%d%c", n, n, n, n, n, n, n, n, '\0');
	
	// write access to shared memory	
	strncpy(pBuf, szMsg, sizeof(szMsg));

	for(i=0; i < 8; ++i)
	{
		printf("\n\t%s", pBuf);
		Sleep(20);
	}

	
	// clean up File Mapping
	MTVERIFY( UnmapViewOfFile(pBuf) );
	MTVERIFY( CloseHandle(hMapFile) );

	// synchronization
	MTVERIFY( ReleaseMutex(hMutex) );
	MTVERIFY( CloseHandle(hMutex) );

	printf("\n\tThread %d idle", n);

	return EXIT_SUCCESS;
} // ThreadFunc