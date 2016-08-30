/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms737526(v=vs.85).aspx
 */

#include <WinSock2.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf ("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	// Create a SOCKET for listening for incoming connection requests.
	SOCKET ListenSocket;
	ListenSocket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf ("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	if (bind (ListenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		printf ("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}


	// Listen for incoming connection requests on the created socket.
	if (listen(ListenSocket, 1) == SOCKET_ERROR)
	{
		printf ("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	
	printf ("Waiting for client to connect ...\n");

	// Create a SOCKET for connected client address.
	SOCKET AcceptSocket;
	AcceptSocket = accept (ListenSocket, NULL, NULL);
	if (AcceptSocket = INVALID_SOCKET)
	{
		printf ("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	printf ("Client connected.\n");

	// No longer need server socket
	closesocket(ListenSocket);
	WSACleanup();
	return 0;	
}