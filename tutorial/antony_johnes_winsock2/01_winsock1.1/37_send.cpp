/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms740149(v=vs.85).aspx
 *
 * The send function sends data on a connected socket.
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
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	
	// Create a SOCKET for connecting to server
	SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}


	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	struct sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(27015);

	// Connect to server.
	iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (iResult == SOCKET_ERROR) 
	{
		printf("connect failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}


	// Send an initial buffer
	const char *sendbuf = "Client: sending data test";
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) 
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %d\n", iResult);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	
	
	const int RECV_BUFLEN = 512;
	char recvbuf[RECV_BUFLEN] = "";

	// Receive until the peer closes the connection
	do 
	{
		iResult = recv (ConnectSocket, recvbuf, RECV_BUFLEN, 0);
		if (iResult > 0)		printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)	printf("Connection closed\n");
		else					printf("recv failed with error: %d\n", WSAGetLastError());
	}
	while (iResult > 0);


	// close the socket
	iResult = closesocket(ConnectSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf("close failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;
}