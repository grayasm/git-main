/*
 * Sub chapter "Connectionless Communication"  ( UDP/IP protocol )
 * MSDN sample from recvfrom(...)
 */


#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>



int main(int argc, char** argv)
{
	int iResult;
	WSADATA wsaData;

	// Initialize Winsock.
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf ("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}


	// Create a receiver socket to receive datagrams.
	SOCKET RecvSocket;
	RecvSocket = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (RecvSocket == INVALID_SOCKET)
	{
		printf ("socket failed with error: %d\n", WSAGetLastError());
		return 1;
	}


	// Bind the socket to any address and the specified port.
	sockaddr_in RecvAddr;
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(27015);
	RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);


	iResult = bind (RecvSocket, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
	if (iResult != 0)
	{
		printf ("bind failed with error: %d\n", WSAGetLastError());
		return 1;
	}

	// Call the recvfrom function to receive datagrams on the bound socket.
	printf ("Receiving datagrams ...\n");
	
	char recvbuf[1024];
	sockaddr_in SenderAddr;
	int SenderAddrSize = (int) sizeof(SenderAddr);
	iResult = recvfrom (RecvSocket, recvbuf, 1024, 0, (SOCKADDR*)&SenderAddr, &SenderAddrSize);

	if (iResult == SOCKET_ERROR)
	{
		printf ("recvfrom failed with error %d\n", WSAGetLastError());
	}
	else
	{
		recvbuf[iResult] = '\0';
		printf ("recvfrom %d: %s\n", iResult, recvbuf);
	}

	// Close the socket when finished receiving datagrams.
	printf ("Finished receiving. Closing socket.\n");

	iResult = closesocket(RecvSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf ("closesocket failed with error %d\n", WSAGetLastError());
		return 1;
	}

	// Clean up and exit.
	printf ("Exiting.\n");
	WSACleanup();
	return 0;
}