/*
  Copyright (C) 2009 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
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
