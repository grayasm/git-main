/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738573(v=vs.85).aspx
 *
 * The ioctlsocket function controls the I/O mode of a socket.
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

	// Create a SOCKET object.
	SOCKET ioSocket;
	ioSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ioSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Set the socket I/O mode: In this case FIONBIO enables or disables the
	// blocking mode for the socket based on the numerical value of iMode.
	// If iMode == 0, blocking is enabled;
	// If iMode != 0, non-blocking mode is enabled.
	u_long iMode = 0;
	iResult = ioctlsocket(ioSocket, FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %d\n", iResult);
	}

	WSACleanup();
	return 0;
}