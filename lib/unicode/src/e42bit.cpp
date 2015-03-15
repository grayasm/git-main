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



#include "e42bit.hpp"

namespace unicode
{
    //
    ////! e42bit is internal byte encoding.
    ////! This string representation can store up to 7 unsigned char (byte) for one unsigned int (32 bit) value.
    ///*
    //  e42bit 8 bytes: 11111111 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    //  e42bit 7 bytes: 11111110 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    //  e42bit 6 bytes: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    //  e42bit 5 bytes: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    //  e42bit 4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    //  e42bit 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
    //  e42bit 2 bytes: 110xxxxx 10xxxxxx

    //  e42bit 1 byte : 0xxxxxxx
    //*/
    //bool u2e42bit(unsigned int ucode, unsigned char e42bit[7], unsigned short& count, bool throw_)
    //{

    //  //first 42 bits are 0 ; next 22 bits are 1; -> maxim 42 bits can be encoded out of 64 (8 bytes)
    //  //unsigned long long _42bitMask = 0xFFFFFC0000000000;

    //  //next only 4 bytes values will be used
    //  if((ucode & 0x80000000) > 0)
    //  {
    //      //7 bytes encoding
    //      e42bit[0] = 0xFE;
    //      e42bit[1] = 0x80 | ((ucode >> 30) & 0x3F);
    //      e42bit[2] = 0x80 | ((ucode >> 24) & 0x3F);
    //      e42bit[3] = 0x80 | ((ucode >> 18) & 0x3F);
    //      e42bit[4] = 0x80 | ((ucode >> 12) & 0x3F);
    //      e42bit[5] = 0x80 | ((ucode >> 6) & 0x3F);
    //      e42bit[6] = 0x80 | (ucode & 0x3F);
    //      count = 7;
    //      return true;
    //  }
    //  else if((ucode & 0xFC000000) > 0)
    //  {
    //      //6 bytes encoding
    //      e42bit[0] = 0xFC | ((ucode >> 30) & 0x1);
    //      e42bit[1] = 0x80 | ((ucode >> 24) & 0x3F);
    //      e42bit[2] = 0x80 | ((ucode >> 18) & 0x3F);
    //      e42bit[3] = 0x80 | ((ucode >> 12) & 0x3F);
    //      e42bit[4] = 0x80 | ((ucode >> 6) & 0x3F);
    //      e42bit[5] = 0x80 | (ucode & 0x3F);
    //      count = 6;
    //      return true;
    //  }
    //  else if((ucode & 0xFFE00000) > 0)
    //  {
    //      //5 bytes encoding
    //      e42bit[0] = 0xF8 | ((ucode >> 24) & 0x3);
    //      e42bit[1] = 0x80 | ((ucode >> 18) & 0x3F);
    //      e42bit[2] = 0x80 | ((ucode >> 12) & 0x3F);
    //      e42bit[3] = 0x80 | ((ucode >> 6) & 0x3F);
    //      e42bit[4] = 0x80 | (ucode & 0x3F);
    //      count = 5;
    //      return true;
    //  }
    //  else if((ucode & 0xFFFF0000) > 0)
    //  {
    //      //4 bytes encoding
    //      e42bit[0] = 0xF0 | ((ucode >> 18) & 0x7);
    //      e42bit[2] = 0x80 | ((ucode >> 12) & 0x3F);
    //      e42bit[3] = 0x80 | ((ucode >> 6) & 0x3F);
    //      e42bit[4] = 0x80 | (ucode & 0x3F);
    //      count = 4;
    //      return true;
    //  }
    //  else if((ucode & 0xFFFFF800) > 0)
    //  {
    //      //3 bytes encoding
    //      e42bit[0] = 0xE0 | ((ucode >> 12) & 0xF);
    //      e42bit[1] = 0x80 | ((ucode >> 6) & 0x3F);
    //      e42bit[2] = 0x80 | (ucode & 0x3F);
    //      count = 3;
    //      return true;
    //  }
    //  else if((ucode & 0xFFFFFF80) > 0)
    //  {
    //      //2 bytes encoding

    //  }
    //  else
    //  {
    //      //1 byte encoding
    //  }


    //  else if((ucode & 0xFFFF0000) > 0 )
    //  {
    //      //"utf-8 has 4 bytes
    //      utf8[0]=0xF0 | (ucode >> 18) & 0xF;
    //      utf8[1]=0x80 | (ucode >> 12) & 0x3F;
    //      utf8[2]=0x80 | (ucode >> 6) & 0x3F;
    //      utf8[3]=0x80 | (ucode & 0x3F);
    //      count=4;
    //      return true;
    //  }
    //  else if((ucode & 0xFFFFFC00) > 0 )
    //  {
    //      //utf-8 has 3 bytes
    //      utf8[0]=0xE0 | (ucode >> 12) & 0xF;
    //      utf8[1]=0x80 | (ucode >> 6) & 0x3F;
    //      utf8[2]=0x80 | (ucode & 0x3F);
    //      count=3;
    //      return true;
    //  }
    //  else if((ucode & 0xFFFFFF80) > 0 )
    //  {
    //      //utf-8 has 2 bytes
    //      utf8[0]=0xC0 | (ucode >> 6) & 0xF;
    //      utf8[1]=0x80 | (ucode & 0x3F);
    //      count=2;
    //      return true;
    //  }
    //  else
    //  {
    //      //utf-8 has 1 bytes
    //      utf8[0]=ucode & 0x7F;
    //      count=1;
    //      return true;
    //  }
    //};
    //bool e42bit2u(unsigned int& ucode, unsigned char e42bit[4], unsigned short& count, bool throw_);
    //bool u2e42bit(unsigned int ucode, e42bitstring& e42bit, unsigned short& count, bool throw_);
    //bool e42bit2u(unsigned int& ucode, const e42bitstring& e42bit, size_t begin, unsigned short& count, bool throw_);

};//namespace
