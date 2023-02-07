/*
Copyright (C) 2013 Mihai Vasilian
*/



#ifndef __unistd_hpp__
#define __unistd_hpp__


#if !defined _WIN32
//non-windows
#include <unistd.h>


#else   // _WIN32

/* This file intended to serve as a drop-in replacement for 
 *  unistd.h on Windows
 *  Please add functionality as needed 
 */

#include <stdlib.h>
#include <io.h>
//#include <getopt.h> /* getopt from: http://www.pwilson.net/sample.html. */
#include <process.h> /* for getpid() and the exec..() family */

#define srandom srand
#define random rand

/* Values for the second argument to access.
   These may be OR'd together.  */
#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
//#define   X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK    0       /* Test for existence.  */



/*  The POSIX name for this item is deprecated. 
    Instead, use the ISO C++ conformant name: _(name). 
    See online help for details.
*/
#define access _access
#define ftruncate _chsize
#define chmod _chmod
#define fcvt _fcvt
#define gcvt _gcvt

// sleep for the specified number of seconds
unsigned int sleep(unsigned int seconds);

#define ssize_t int

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
/* should be in some equivalent to <sys/types.h> */
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

/*
typedef __int8            int8_t;
typedef __int16           int16_t; 
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;
*/

#endif // _WIN32


//clears the console screen
void clrscr();

// sleep for the specified number of milliseconds
int	msleep(unsigned long milliseconds);




#endif // __unistd_hpp__