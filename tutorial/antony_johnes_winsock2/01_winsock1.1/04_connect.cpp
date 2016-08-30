/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms737625(v=vs.85).aspx
 */

#include <WinSock2.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("WSAStartup function failed with error: %d\n", iResult);        
		return 1;
	}

	// Create a SOCKET for connecting to server
	SOCKET ConnectSocket;
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("socket function failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// The sockaddr_in structure specifies the address family,
	// IP address and port of the server to be connected to.
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(27015);


	// Connect to server.
	iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (iResult == SOCKET_ERROR)
	{
		printf("connect function failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Connected to server.\n");

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	iResult = closesocket(ConnectSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket function failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;


	
}