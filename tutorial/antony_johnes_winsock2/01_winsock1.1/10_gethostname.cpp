/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738527(v=vs.85).aspx
 *
 * The gethostname function retrieves the standard host name for 
 * the local computer.
 */

#include <WinSock2.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	char host[201];
	iResult = gethostname(host, 200);
	if (iResult == SOCKET_ERROR)
	{
		printf("gethostname failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	printf("gethostname returned: %s\n", host);

	WSACleanup();
	return 0;
}