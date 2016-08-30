/*
* https://msdn.microsoft.com/en-us/library/windows/desktop/ms738544(v=vs.85).aspx
*
* The getsockopt function retrieves a socket option.
* Second sample from MSDN.
*/

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <AF_Irda.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %s\n", iResult);
		return 1;
	}

	SOCKET Sock = INVALID_SOCKET;
	Sock = socket(AF_IRDA, SOCK_STREAM, 0);
	if (Sock == INVALID_SOCKET)
	{
		DWORD dwError = WSAGetLastError();
		printf("socket failed trying to create an AF_IRDA socket with error: %d\n", dwError);
		if (dwError == WSAEAFNOSUPPORT)
		{
			printf("Check that the local computer has an infrared device\n");
			printf("and a device driver is installed for it.\n");
		}
		WSACleanup();
		return 1;
	}

	

	PDEVICELIST pDevList;
	const int DEVICE_LIST_LEN = 10;
	unsigned char DevListBuff[	sizeof(DEVICELIST) - 
								sizeof(IRDA_DEVICE_INFO) +
								(sizeof(IRDA_DEVICE_INFO) * DEVICE_LIST_LEN)];
	int DevListLen = sizeof(DevListBuff);
	pDevList = (PDEVICELIST)&DevListBuff;

	// Sock is not in connected state
	iResult = getsockopt(	Sock, 
							SOL_IRLMP, 
							IRLMP_ENUMDEVICES,
							(char*)pDevList, 
							&DevListLen);

	if (iResult == SOCKET_ERROR)
	{
		printf("getsockopt failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	if (pDevList->numDevice == 0)
	{
		// no devices discovered or cached
		printf("No IRDA devices were discovered or cached.\n");
		WSACleanup();
		return 1;
	}

	for (int i = 0; i < (int)pDevList->numDevice; i++)
	{
		// typedef struct _IRDA_DEVICE_INFO
		// {
		//     u_char    irdaDeviceID[4];
		//     char      irdaDeviceName[22];
		//     u_char    irdaDeviceHints1;
		//     u_char    irdaDeviceHints2;
		//     u_char    irdaCharSet;
		// } _IRDA_DEVICE_INFO;

		printf("\tDeviceName #%d: %s\n", i, pDevList->Device[i].irdaDeviceName);
	}

	// assume the user selected the first device [0]
	SOCKADDR_IRDA DestSockAddr = { AF_IRDA, 0, 0, 0, 0, "SampleIrDAService" };
	memcpy(&DestSockAddr.irdaDeviceID[0], &pDevList->Device[0].irdaDeviceID[0], 4);

	iResult = connect(	Sock, 
						(const struct sockaddr*) &DestSockAddr,
						sizeof(SOCKADDR_IRDA));

	if (iResult == SOCKET_ERROR)
	{
		printf("connect failed with error: %d\n", WSAGetLastError());
	}
	else
	{
		printf("connect to first IRDA device was successful\n");
	}

	WSACleanup();
	return 0;
}