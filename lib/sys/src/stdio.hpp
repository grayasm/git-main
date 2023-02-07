/*
Copyright (C) 2009 Mihai Vasilian
*/


#ifndef __stdio_hpp__
#define __stdio_hpp__

#include <stdio.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif


#ifdef _WIN32
#define unlink _unlink
#endif



/*00 existence*/
/*02 write only*/
/*04 read only*/
/*06 read and write*/
#define F_EXIST 0
#define F_WONLY 1 << 1
#define F_RONLY 1 << 2
#define F_WR    F_WONLY | F_RONLY


#ifdef _WIN32
#   ifdef _UNICODE
#       define access _waccess
#else
#       define access _access
#   endif
#endif


#endif//__stdio_hpp__
