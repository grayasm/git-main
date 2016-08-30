/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738520(v=vs.85).aspx
 *
 * Example code using AI_NUMERICHOST
 */

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	WSADATA wsaData;

	// Initializing Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	// Setup the hints address info structure which is passed to the
	// getaddrinfo() function.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_flags = AI_NUMERICHOST;
	hints.ai_family = AF_UNSPEC;
	// extra
	// hints.ai_socktype = SOCK_STREAM;
	// hints.ai_protocol = IPPROTO_TCP;

	// Call getaddrinfo() If the call succeeds the result variable will hold
	// a linked list of addrinfo structures containing response information.
	DWORD dwRetval;
	struct addrinfo* result = NULL;
	dwRetval = getaddrinfo("64.4.6.100", NULL, &hints, &result); // www.contoso.com from 07_getaddrinfo
	if (dwRetval != NO_ERROR)
	{
		printf("getaddrinfo failed with error: %d\n", dwRetval);
		WSACleanup();
		return 1;
	}

	printf("getaddrinfo returned success\n");

	int i = 1;
	struct addrinfo* ptr = NULL;
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		printf("getaddrinfo response %d\n", i++);
		printf("\tFlags : 0x%x\n", ptr->ai_flags);
		printf("\tFamily: ");
		switch (ptr->ai_family)
		{
		case AF_UNSPEC:
			printf("Unspecified\n");
			break;

		case AF_INET:
			printf("AF_INET (IPv4)\n");
			break;

		case AF_INET6:
			printf("AF_INET6 (IPv6)\n");
			break;

		case AF_NETBIOS:
			printf("AF_NETBIOS (NetBIOS)\n");
			break;

		default:
			printf("Other %d\n", ptr->ai_family);
			break;
		} // ptr->ai_family

		printf("Socket type: ");
		switch (ptr->ai_socktype)
		{
		case 0:
			printf("Unspecified\n");
			break;

		case SOCK_STREAM:
			printf("SOCK_STREAM (stream)\n");
			break;

		case SOCK_DGRAM:
			printf("SOCK_DGRAM (datagram)\n");
			break;

		case SOCK_RAW:
			printf("SOCK_RAW (raw)\n");
			break;

		case SOCK_RDM:
			printf("SOCK_RDM (reliable message datagram)\n");
			break;

		case SOCK_SEQPACKET:
			printf("SOCK_SEQPACKET (pseudo-stream packet)\n");
			break;

		default:
			printf("Other %d\n", ptr->ai_socktype);
			break;
		} // ptr->ai_socktype

		printf("\tProtocol: ");
		switch (ptr->ai_protocol)
		{
		case 0:
			printf("Unspecified\n");
			break;

		case IPPROTO_TCP:
			printf("IPPROTO_TCP (TCP)\n");
			break;

		case IPPROTO_UDP:
			printf("IPROTO_UDP (UDP)\n");
			break;

		default:
			printf("Other %d\n", ptr->ai_protocol);
			break;
		} // ptr->ai_protocol

		printf("\tLength of this sockaddr: %d\n", ptr->ai_addrlen);
		printf("\tCanonical name: %s\n", ptr->ai_canonname);
	} // for(ptr)

	freeaddrinfo(result);
	WSACleanup();
	return 0;
}
