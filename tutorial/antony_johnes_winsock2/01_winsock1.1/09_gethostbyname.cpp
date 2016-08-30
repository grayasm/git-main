/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738524(v=vs.85).aspx
 *
 * The gethostbyname function retrieves host information corresponding 
 * to a host name from a host database.
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

	printf("Calling gethostbyname with www.contoso.com \n");


	struct hostent* remoteHost;
	remoteHost = gethostbyname("www.contoso.com"); // or "127.0.0.1"
	if (remoteHost == NULL)
	{
		DWORD dwError = WSAGetLastError();
		if (dwError == WSAHOST_NOT_FOUND) printf("Host not found\n");
		else if (dwError == WSANO_DATA) printf("No data record found\n");
		else printf("Function failed with error: %d\n", dwError);
		return 1;
	}

	int i = 0;
	char** pAlias;
	printf("Function returned:\n");
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

	case AF_NETBIOS:
		printf("AF_NETBIOS \n");
		break;

	default:
		printf(" %d\n", remoteHost->h_addrtype);
		break;
	}

	printf("\tAddress length: %d\n", remoteHost->h_length);

	i = 0;
	struct in_addr addr;
	if (remoteHost->h_addrtype == AF_INET)
	{
		while (remoteHost->h_addr_list[i] != 0)
		{
			addr.s_addr = *(u_long *)remoteHost->h_addr_list[i++];
			printf("\tIP Address #%d: %s\n", i, inet_ntoa(addr));
		}
	}
	else if (remoteHost->h_addrtype == AF_NETBIOS)
	{
		printf("NETBIOS address was returned \n");
	}

	WSACleanup();
	return 0;
}