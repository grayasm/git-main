// IOCTLS.H -- IOCTL code definitions for memtest driver
// Copyright (C) 1999, 2000 by Walter Oney
// All rights reserved

#ifndef IOCTLS_H
#define IOCTLS_H

#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif

#define IOCTL_DO_TEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#endif
