/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738532(v=vs.85).aspx
 *
 * The getnameinfo function provides protocol-independent name resolution 
 * from an address to an ANSI host name and from a port number to the ANSI
 * service name.
 */

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %s\n", iResult);
		return 1;
	}

	// Set up sockaddr_in structure which is passed to the getnameinfo
	struct sockaddr_in saGNI;
	saGNI.sin_family = AF_INET;
	saGNI.sin_addr.s_addr = inet_addr("127.0.0.1");
	saGNI.sin_port = htons(27015);

	// Call getnameinfo
	DWORD dwRetval;
	char hostname[NI_MAXHOST];
	char servInfo[NI_MAXSERV];

	dwRetval = getnameinfo(	(struct sockaddr*) &saGNI,
							sizeof(struct sockaddr),
							hostname,
							NI_MAXHOST,
							servInfo,
							NI_MAXSERV,
							NI_NUMERICSERV);

	if (dwRetval != 0)
	{
		printf("getnameinfo failed with error %d\n", WSAGetLastError());
		return 1;
	}

	printf("getnameinfo returned hostname = %s\n", hostname);
	
	WSACleanup();
	return 0;
}