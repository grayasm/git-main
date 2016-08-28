/*
 */
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	// Initialize Winsock.
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf ("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	// Create a SOCKET for listening for incoming connection requests.
	SOCKET ListenSocket;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	if (bind(ListenSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR)
	{
		printf ("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}


	// Listen for incoming connection requests on the created socket.
	if (listen(ListenSocket, 1) == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}


	// Create a SOCKET for accepting incoming requests.
	printf ("Waiting for client to connect ...\n");
	SOCKET ClientSocket;	
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	printf("Client connected.\n");

	// MSDN example "Receiving and Sending Data on the Server"
	char recvbuf[512];
	int iSendResult;

	do 
	{
		iResult = recv(ClientSocket, recvbuf, 512, 0);
		if (iResult > 0)
		{
			printf ("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);

			if (iSendResult == SOCKET_ERROR)
			{
				printf ("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}

			printf ("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
		{
			printf ("Connection closing ...\n");
		}
		else
		{
			printf ("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);


	// No longer need server socket.
	printf ("server shutting down\n");
	closesocket(ListenSocket);
	WSACleanup();
	return 0;
}