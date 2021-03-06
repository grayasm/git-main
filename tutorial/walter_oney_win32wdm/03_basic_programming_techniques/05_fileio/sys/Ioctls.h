/*
	IOCTLS.H -- IOCTL code definitions for fileio driver
	Copyright (C) 1999 by Walter Oney
*/



#ifndef IOCTLS_H
#define IOCTLS_H

#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif

#define IOCTL_READ_FILE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif
