#include <winsock2.h>
#include <stdio.h>

void main(void)
{
	int Ret;
	WSADATA wsaData;
	
	// Initialize Winsock version 2.2
	if ((Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
	{
		// NOTE: Since Winsock failed to load we cannot use 
		// WSAGetLastError to determine the specific error for
		// why it failed. Instead we can rely on the return 
		// status of WSAStartup.
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}
	// Setup Winsock communication code here 
	// When your application is finished call WSACleanup
	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("WSACleanup failed with error %d\n", WSAGetLastError());
	}
}