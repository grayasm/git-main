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


#include "exception.hpp"




namespace unicode
{

    //! utf8 string representation. One character utf8 encoded, may contain 1,2,3 or 4 bytes.
    //! It can store unicode code point value with up to 22 bits
    /*
      utf8 4 bytes: 1111xxxx 10xxxxxx 10xxxxxx 10xxxxxx
      utf8 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
      utf8 2 bytes: 1100xxxx 10xxxxxx
      utf8 1 byte : 0xxxxxxx
    */

    typedef std::basic_string<unsigned char> utf8string;

    bool u2utf8(unsigned int ucode, unsigned char utf8[4], unsigned short& count, bool throw_);
    bool utf82u(unsigned int& ucode, unsigned char utf8[4], unsigned short& count, bool throw_);
    bool u2utf8(unsigned int ucode, utf8string& utf8, unsigned short& count, bool throw_);
    bool utf82u(unsigned int& ucode, const utf8string& utf8, size_t begin, unsigned short& count, bool throw_);

}//namespace


