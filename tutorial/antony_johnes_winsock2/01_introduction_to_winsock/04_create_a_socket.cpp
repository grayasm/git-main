#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	// Initialize Winsock.
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	int iFamily[] = {	AF_UNSPEC,		// Unspecified
						AF_INET,		// IPv4
						AF_INET6,		// IPv6
						AF_NETBIOS,		// NetBIOS
						AF_BTH			// Bluetooth
	};
	int iType[] = {		0,					// Unspecified
						SOCK_STREAM,		// stream
						SOCK_DGRAM,			// datagram
						SOCK_RAW,			// raw
						SOCK_RDM,			// reliable message datagram
						SOCK_SEQPACKET		// pseudo-stream packet
	};
	int iProtocol[] = {	0,					// Unspecified
						IPPROTO_ICMP,		// ICMP
						IPPROTO_IGMP,		// IGMP
						IPPROTO_TCP,		// TCP (Transmission Control Protocol)
						IPPROTO_UDP,		// UDP (User Data Protocol)
						IPPROTO_ICMPV6		// ICMP Version 6
	};
	
	SOCKET sock = INVALID_SOCKET;
	//            AF_NET      SOCK_STREAM   IPPROTO_TCP
	sock = socket(iFamily[1], iType[1], iProtocol[3]);
	if (sock == INVALID_SOCKET)
	{
		printf("socket function failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	printf ("socket function succeeded\n");

	// test the returned 
	iResult = closesocket(sock);
	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;
}