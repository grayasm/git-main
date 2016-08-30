/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738544(v=vs.85).aspx
 *
 * The getsockopt function retrieves a socket option.
 * First sample from MSDN.
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
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	// Create a listening socket
	SOCKET ListeningSocket;
	ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListeningSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Bind the socket to the local IP address and port 27015
	struct hostent* host;
	host = gethostbyname(""); // this host
	char* ip = inet_ntoa(*(struct in_addr*)*host->h_addr_list);

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(27015);

	if (bind(ListeningSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return 1;
	}

	// Initialize variables and call getsockopt.
	// The SO_ACCEPTCONN parameter is a socket option that tells the function
	// to check whether the socket has been put in listening mode or not.
	// The various socket options return different information about the socket.
	// This call should return 0 to the optVal parameter, since the socket
	// is not in listening mode.
	int optVal;
	int optLen = sizeof(int);

	iResult = getsockopt(ListeningSocket, 
						 SOL_SOCKET,
						 SO_ACCEPTCONN,
						 (char*)&optVal,
						 &optLen);

	if (iResult != SOCKET_ERROR)
	{
		printf("SockOpt Value: %d\n", optVal);
	}

	// Put the listening socket is listening mode.
	iResult = listen(ListeningSocket, 100);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return 1;
	}
	

	// Call getsockopt again to verify that the socket is in listening mode.
	iResult = getsockopt(	ListeningSocket,
							SOL_SOCKET,
							SO_ACCEPTCONN,
							(char*)&optVal,
							&optLen);

	if (iResult != SOCKET_ERROR)
	{
		printf("SockOpt Value: %d\n", optVal);
	}

	closesocket(ListeningSocket);
	WSACleanup();
	return 0;
}