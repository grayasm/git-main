/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/cc805844(v=vs.85).aspx
 *
 * The InetPton function converts an IPv4 or IPv6 Internet network address in 
 * its standard text presentation form into its numeric binary form.
 * The ANSI version of this function is inet_pton.
 *
 * An example for inet_pton
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

	printf("Calling gethostbyaddr with 0::1\n");

	IN6_ADDR addr6;
	iResult = inet_pton(AF_INET6, "0::1", &addr6);
	if (iResult == 0)
	{
		printf("The IPv6 address entered must be legal address\n");
		return 1;
	}

	DWORD dwError;
	struct hostent* remoteHost;
	remoteHost = gethostbyaddr((char*)&addr6, 16, AF_INET6);
	if (remoteHost == NULL)
	{
		dwError = WSAGetLastError();
		if (dwError == WSAHOST_NOT_FOUND) printf("Host not found.\n");
		else if (dwError == WSANO_DATA) printf("No data record found.\n");
		else printf("gethostbyaddr failed with error: %d\n", dwError);
		return 1;
	}

	int i = 0;
	char** pAlias;
	printf("Function returned: \n");
	printf("\tOfficial name: %s\n", remoteHost->h_name);
	for (pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++)
	{
		printf("\tAlternate name #%d: %s\n", ++i, *pAlias);
	}

	printf("\tAddress type: ");
	switch (remoteHost->h_addrtype)
	{
	case AF_INET:
		printf("AF_INET \n");
		break;

	case AF_INET6:
		printf("AF_INET6 \n");
		break;

	case AF_NETBIOS:
		printf("AF_NETBIOS \n");
		break;

	default:
		printf(" %d\n", remoteHost->h_addrtype);
		break;
	} // remoteHost->h_addrtype

	printf("\tAddress length: %d\n", remoteHost->h_length);
	if (remoteHost->h_addrtype == AF_INET6)
		printf("\tRemotehost is an IPv6 address\n");


	printf("Calling gethostbyaddr with 127.0.0.1\n");

	struct in_addr addr = { 0 };
	addr.s_addr = inet_addr("127.0.0.1");
	if (addr.s_addr == INADDR_NONE)
	{
		printf("The IPv4 address entered must be a legal address\n");
		return 1;
	}

	remoteHost = gethostbyaddr((char*)&addr, 4, AF_INET);
	if (remoteHost == NULL)
	{
		dwError = WSAGetLastError();
		if (dwError == WSAHOST_NOT_FOUND) printf("Host not found\n");
		else if (dwError = WSANO_DATA) printf("No data record found\n");
		else printf("Function failed with error: %d\n", dwError);
		return 1;
	}

	i = 0;
	printf("Function returned: \n");
	printf("\tOfficial name: %s\n", remoteHost->h_name);
	for (pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++)
	{
		printf("\tAlternate name #%d: %s\n", ++i, *pAlias);
	}

	printf("\tAddress type: ");
	switch (remoteHost->h_addrtype)
	{
	case AF_INET:
		printf("AF_INET \n");
		break;

	case AF_INET6:
		printf("AF_INET6 \n");
		break;

	case AF_NETBIOS:
		printf("AF_NETBIOS \n");
		break;

	default:
		printf(" %d\n", remoteHost->h_addrtype);
		break;
	} // remoteHost->h_addrtype

	i = 0;
	printf("\tAddress length: %d\n", remoteHost->h_length);
	if (remoteHost->h_addrtype == AF_INET)
	{
		while (remoteHost->h_addr_list[i] != 0)
		{
			addr.s_addr = *(u_long *)remoteHost->h_addr_list[i++];
			printf("\tIPv4 Address #%d: %s\n", i, inet_ntoa(addr));
		}
	}


	WSACleanup();
	return 0;
}