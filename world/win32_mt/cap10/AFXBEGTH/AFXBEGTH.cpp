/*
 * This is book NUMBERS.CPP from Listing 10-1
 * Creating worker threads with AfxBeginThread()
 *
 * Demonstrates how to use the MFC thread
 *              with AfxBeginThread()
 */

#include <afxwin.h>

CWinApp TheApp;

UINT ThreadFunc(LPVOID);

int main()
{
	for(int i=0; i < 5; ++i)
	{
		if( AfxBeginThread(ThreadFunc, (LPVOID)i) )
			printf("Thread launched %d\n", i);
	}

	// Wait for the threads to complete
	Sleep(2000);

	printf("Exit\n\n");

	return 0;
} // main

UINT ThreadFunc(LPVOID n)
{
	for(int i=0; i<10; i++)
		printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
	
	return 0;
}
