/*
 * It's normal sample for creating the socket, connecting and closing the 
 * connection +  + book sample from "Connection Oriented Communication"
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

	// -------------------------------------------------------
	// "Connection Oriented Communication" : Stream protocols
	// 2 issues here:
	// 1) send(...) sends the buffer in smaller chunks (3rd param 36 != 259)
	// 2) send(...) must check how many bytes has the peer received and
	//              start from there with the next call.
	//              
	// Observation: at run-time the client always confirms 36 bytes sent.
	// However the server's buffer is 50 bytes which is bigger than the client 
	// buffer and it receives 36 bytes what was sent but sometimes also 
	// maximum 50 bytes which means send(..) calls got buffered.

	const char* sendbuf =	"0123456789abcdefghijklmnopqrstuvwxyz" // 36
							"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" // 72
							"+0+1+2+3+4+5+6+7+8+9+8+7+6+5+4+3+2+1" // 108
							"A-B-C-D-E-F-G-H-I-J-K-L-M-N-O-P-Q-R-" // 144
							"a+c+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+" // 180
							"0+1i+2i+3i+4i+5i+6i+7i+8i+9i+AAi+BBi" // 216
							"-0-1-2-3-4-5-6-7-8-9-8-7-6-5-4-3-2-1" // 252
							">>EOF<<";                             // 259
	
	int iTotal = (int) strlen(sendbuf);
	int iPos = 0;
	int iSent = 0;
	int iSize = min(iTotal, 36); // send 1 line per call.
	
	while (iTotal > 0)
	{
		iSent = send(ConnectSocket, &sendbuf[iPos], iSize, 0);
		if (iSent == SOCKET_ERROR)
		{
			printf ("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		char subbuf[300];
		memcpy(subbuf, &sendbuf[iPos], iSent);
		subbuf[iSent] = '\0';
		printf ("sent %d: %s\n", iSent, subbuf);

		iSize -= iSent;
		iPos += iSent;
		iTotal -= iSent;
		if (iSize == 0) iSize = min(iTotal, 36); // send 1 line per call.
	}

	

	printf ("Client shutting down!\n");

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

	// end of sample
	// -------------------------------------------------------


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