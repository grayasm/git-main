/*
 */

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	// Initialize Winsock
	WSADATA wsaData;
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
	// IP address, and port of the server to be connected to.
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port  = htons(27015);


	// Connecting to server.
	iResult = connect(ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService));
	if (iResult == SOCKET_ERROR)
	{
		printf ("connect function failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}


	printf ("Connected to server.\n");

	// MSDN example "Sending and Receiving Data on the Client"

	const char* sendbuf = "this is a test";
	char recvbuf[512];
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf ("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf ("Bytes sent: %d\n", iResult);

	// shutdown the connection for sending since no more data will be sent
	// ConnectSocket can still be used for receiving data
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf ("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// Receive data until the server closes the connection
	do 
	{
		iResult = recv (ConnectSocket, recvbuf, 512, 0);

		if (iResult > 0) printf ("Bytes received: %d\n", iResult);
		else if (iResult == 0) printf ("Connection closed\n");
		else printf ("recv failed with error: %d\n", WSAGetLastError());
	} while (iResult > 0);



	iResult = closesocket(ConnectSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf ("closesocket function failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;
}