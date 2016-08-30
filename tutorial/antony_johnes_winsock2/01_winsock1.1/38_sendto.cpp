/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms740148(v=vs.85).aspx
 *
 * The sendto function sends data to a specific destination.
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

	// Create a socket for sending data
	SOCKET SendSocket = INVALID_SOCKET;
	SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendSocket == INVALID_SOCKET) 
	{
		printf("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Set up the RecvAddr structure with the IP address of
	// the receiver (in this example case "192.168.1.1")
	// and the specified port number.
	sockaddr_in RecvAddr;
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(27015);
	RecvAddr.sin_addr.s_addr = inet_addr("192.168.1.1");

	
	printf("Sending a datagram to the receiver...\n");

	// Send a datagram to the receiver
	const int BUFLEN = 1024;
	char SendBuf[BUFLEN];

	iResult = sendto(SendSocket, SendBuf, BUFLEN, 0, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr));
	if (iResult == SOCKET_ERROR) 
	{
		printf("sendto failed with error: %d\n", WSAGetLastError());
		closesocket(SendSocket);
		WSACleanup();
		return 1;
	}

	printf("Finished sending. Closing socket.\n");

	iResult = closesocket(SendSocket);
	if (iResult == SOCKET_ERROR) 
	{
		printf("closesocket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}


	// Clean up and quit.
	printf("Exiting.\n");
	WSACleanup();
	return 0;
}
