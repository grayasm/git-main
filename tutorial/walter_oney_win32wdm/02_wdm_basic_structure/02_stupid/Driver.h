// Declarations for stupid driver
// Copyright (C) 1999, 2000 by Walter Oney
// All rights reserved

#pragma once

#define DRIVERNAME "STUPID"				// for use in messages
#define LDRIVERNAME L"STUPID"				// for use in UNICODE string constants

///////////////////////////////////////////////////////////////////////////////
// Device extension structure

typedef struct _DEVICE_EXTENSION {
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT LowerDeviceObject;		// next lower driver in same stack
	PDEVICE_OBJECT Pdo;						// the PDO
	UNICODE_STRING ifname;					// interface name
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
