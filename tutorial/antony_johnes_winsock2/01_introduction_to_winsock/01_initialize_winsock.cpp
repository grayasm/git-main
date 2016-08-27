/*
 * If you request a Winsock version later than that which the platform supports,
 * WSAStartup will fail. Upon return, the wHighVersion of the WSADATA structure 
 * will be the latest version supported by the library on the current system. 
 */

#include <WinSock2.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	WSADATA wsdata;

	// Request to initialize WinSock 5.0
	// The book says it must fail but it doesn't.
	// It also fills in the current and high supported WinSock version.
	int ret = WSAStartup(MAKEWORD(5,0), &wsdata);

	printf("WinSock initialized with version: %d %d\n",
		LOBYTE(wsdata.wVersion),
		HIBYTE(wsdata.wVersion));

	printf("WinSock higher supported version: %d %d\n",
		LOBYTE(wsdata.wHighVersion),
		HIBYTE(wsdata.wHighVersion));

	if (ret)
	{
		printf("Failed to initalize WinSock 5.0\n");			
		return -1;
	}

	return 0;
}