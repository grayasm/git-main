/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738564(v=vs.85).aspx
 * 
 * The inet_ntoa function converts an (Ipv4) Internet network address into 
 * an ASCII string in Internet standard dotted-decimal format.
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
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	// Setup the hints address info structure which is passed to the
	// getaddrinfo() function
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Call getaddrinfo()  If the call succeeds, the result variable will
	// hold a linked list of addrinfo structures containing response information.

	struct addrinfo* result = NULL;
	DWORD dwRetval = getaddrinfo("www.contoso.com", "0", &hints, &result);
	if (dwRetval != NO_ERROR)
	{
		printf("getaddrinfo failed with error: %d\n", dwRetval);
		WSACleanup();
	}

	printf("getaddrinfo returned success\n");

	int i = 1;
	struct addrinfo* ptr = NULL;
	struct sockaddr_in* sockaddr_ipv4;
	struct sockaddr_in6* sockaddr_ipv6;
	char ipstringbuffer[46];
	DWORD ipbufferlength = 46;
	LPSOCKADDR sockaddr_ip;
	INT iRetval;

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
			sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
			printf("\tIPv4 address %s\n", inet_ntoa(sockaddr_ipv4->sin_addr));
			break;

		case AF_INET6:
			printf("AF_INET6 (IPv6)\n");
			// the InetNtop function is available on Windows Vista and later
			sockaddr_ipv6 = (struct sockaddr_in6*) ptr->ai_addr;
			printf("\tIPv6 address %s\n",
				InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46));
			sockaddr_ip = (LPSOCKADDR)ptr->ai_addr;

			// The buffer length is changed by each call to WSAAddresstoString
			// So we need to set it for each iteration through the loop for safety.
			ipbufferlength = 46;
			iRetval = WSAAddressToString(sockaddr_ip,
				(DWORD)ptr->ai_addrlen,
				NULL,
				ipstringbuffer,
				&ipbufferlength);
			if (iRetval)
				printf("WSAAddresstoString failed with %d\n", WSAGetLastError());
			else
				printf("\tIPv6 address %s\n", ipstringbuffer);
			break;

		case AF_NETBIOS:
			printf("AF_NETBIOS (NetBIOS)\n");
			break;

		default:
			printf("Other %ld\n", ptr->ai_family);
			break;
		} // ptr->ai_family

		printf("\tSocket type: ");
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
			printf("Other %ld\n", ptr->ai_socktype);
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
			printf("IPPROTO_UDP (UDP)\n");
			break;

		default:
			printf("Other %ld\n", ptr->ai_protocol);
			break;
		}

		printf("\tLength of this sockaddr: %d\n", ptr->ai_addrlen);
		printf("\tCanonical name: %s\n", ptr->ai_canonname);
	} // for (ptr*)

	freeaddrinfo(result);
	WSACleanup();
	return 0;
}