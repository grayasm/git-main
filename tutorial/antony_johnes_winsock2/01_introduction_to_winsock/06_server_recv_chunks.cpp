/*
 * It's normal sample for creating the bind(), listen(), accept() on a
 * connection + book sample from "Connection Oriented Communication"
 */

#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>


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

	// -------------------------------------------------------
	// "Connection Oriented Communication" : Stream protocols
	// Few issues here:
	// 1) buffer is 51, 50 occupied by recv() buffer + NULL termination.
	// 2) client sends buffers of 36 bytes but here sometimes are confirmed
	//    50 bytes which looks like send(...) calls got buffered.
	// 3) search for >>EOF<< otherwise it's not known when to stop recv(...)
	
	std::string recvstr;
	char recvbuf[51];
	int iRecvBytes = 0;
	
	do 
	{
		iRecvBytes = recv(ClientSocket, recvbuf, 50, 0);
		if (iRecvBytes > 0)
		{
			recvbuf[iRecvBytes] = '\0';
			printf ("recv-ed %d: %s\n", iRecvBytes, recvbuf);
			recvstr += recvbuf;

			// search for end of transmission
			if (recvstr.find(">>EOF<<") != std::string::npos)
			{
				printf ("found EOF\n");
				break;
			}
		}
		else if (iRecvBytes == 0)
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
	} while (iRecvBytes > 0);

	// end of sample.
	// -------------------------------------------------------


	// No longer need server socket.
	printf ("Server shutting down\n");
	closesocket(ListenSocket);
	WSACleanup();
	return 0;
}