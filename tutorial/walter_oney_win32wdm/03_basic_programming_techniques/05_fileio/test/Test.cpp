
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"
#include <string>

std::string GetLastErrorAsString();

int main(int argc, char* argv[])
	{							// main
	HANDLE hdevice = CreateFile("\\\\.\\FILEIO", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open FILEIO device - \n"
			   "Error: %s\n", GetLastErrorAsString().c_str());
		return 1;
		}

	char answer[512];
	DWORD junk;
	if (DeviceIoControl(hdevice, IOCTL_READ_FILE, NULL, 0, answer, sizeof(answer), &junk, NULL))
		{
		answer[junk] = 0;
		puts(answer);
		}
	else
		printf("Error %d in call to DeviceIoControl\n", GetLastError());
	
	CloseHandle(hdevice);
	return 0;
	}							// main


std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}