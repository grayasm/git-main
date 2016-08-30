/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms740476(v=vs.85).aspx
 *
 * The setsockopt function sets a socket option.
 */


#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("Error at WSAStartup() \n");
		return 1;
	}

	// Create a listening socket
	SOCKET ListenSocket;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) 
	{
		printf("socket function failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Bind the socket to the local IP address and port 27015
	hostent* thisHost = gethostbyname("");
	char* ip = inet_ntoa(*(struct in_addr *) *thisHost->h_addr_list);

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(27015);

	iResult = bind(ListenSocket, (SOCKADDR *)& service, sizeof(service));
	if (iResult == SOCKET_ERROR) 
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}


	//---------------------------------------
	// Initialize variables and call setsockopt. 
	// The SO_KEEPALIVE parameter is a socket option that makes the socket 
	// send keepalive messages on the session. The SO_KEEPALIVE socket option
	// requires a boolean value to be passed to the setsockopt function. 
	// If TRUE  the socket is configured to send keepalive messages.
	// If FALSE the socket configured to NOT send keepalive messages.
	// This section of code tests the setsockopt function by checking the 
	// status of SO_KEEPALIVE on the socket using the getsockopt function.

	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);

	int iOptVal = 0;
	int iOptLen = sizeof(int);

	iResult = getsockopt(ListenSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&iOptVal, &iOptLen);
	if (iResult == SOCKET_ERROR)
	{
		printf("getsockopt for SO_KEEPALIVE failed with error: %d\n", WSAGetLastError());
	}
	else
	{
		printf("SO_KEEPALIVE Value: %d\n", iOptVal);
	}

	iResult = setsockopt(ListenSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&bOptVal, bOptLen);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"setsockopt for SO_KEEPALIVE failed with error: %d\n", WSAGetLastError());
	}
	else
	{
		printf("Set SO_KEEPALIVE: ON\n");
	}

	iResult = getsockopt(ListenSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&iOptVal, &iOptLen);
	if (iResult == SOCKET_ERROR) 
	{
		printf("getsockopt for SO_KEEPALIVE failed with error: %d\n", WSAGetLastError());
	}
	else
	{
		printf("SO_KEEPALIVE Value: %d\n", iOptVal);
	}

	closesocket(ListenSocket);
	WSACleanup();
	return 0;
}