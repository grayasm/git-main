/*
 * Sub chapter "Connectionless Communication"  ( UDP/IP protocol )
 * MSDN sample from sendto(...) modified to call connect() + send()
 * See README.txt for the second alternative with explicit target.
 */



#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	int iResult;
	WSADATA wsaData;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf ("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	// Create socket for sending data.
	SOCKET SendSocket;
	SendSocket = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendSocket == INVALID_SOCKET)
	{
		printf ("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Set up the sockaddr_in structure with the address+port of the receiver.
	sockaddr_in  RecvAddr;
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(27015);
	RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	// Connecting to server.
	iResult = connect(SendSocket, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
	if (iResult == SOCKET_ERROR)
	{
		printf("connect function failed with error: %d\n", WSAGetLastError());
		closesocket(SendSocket);
		WSACleanup();
		return 1;
	}


	// Send the datagram to the receiver.
	printf ("Sending a datagram to the receiver ...\n");

	const char* sendbuf = "This is the entire datagram text. "
						  "is the entire datagram text. This "
						  "the entire datagram text. This is "
						  "entire datagram text. This is the "
						  "datagram text. This is the entire "
						  "text. This is the entire datagram "
						  "This is the entire datagram text. ";
	
	int buflen = (int) strlen(sendbuf);

	iResult = send(SendSocket, sendbuf, buflen, 0);
	if (iResult == SOCKET_ERROR)
	{
		printf ("sendto failed with error: %d\n", WSAGetLastError());
		closesocket(SendSocket);
		WSACleanup();
		return 1;
	}

	printf ("send %d: %s\n", iResult, sendbuf);

	// When the application is finished sending, close the socket.
	iResult = closesocket(SendSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf ("closesocket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}


	// Clean up and quit.
	printf ("Exiting.\n");
	WSACleanup();
	return 0;
}