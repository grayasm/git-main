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



#include "utf8.hpp"

namespace unicode
{
    bool u2utf8(unsigned int ucode, unsigned char utf8[4], unsigned short& count, bool throw_)
    {
        //if ucode value is on more than 22 bits
        if((ucode & 0xffffffff) > 0x3fffff)
        {
            if(throw_)
            {
                throw misc::exception("u2utf8 more than 22 bits in unicode code point value.");
            }
            else
            {
                count = 0;
                return false;
            }
        }

        //utf8 1 byte : 0xxxxxxx
        //test if ucode smaller than binary: 10000000 = 0x80
        if((ucode & 0xffffffff) < 0x80 )
        {
            //utf-8 has 1 bytes
            utf8[0]=ucode & 0x7F;
            count=1;
            return true;
        }

        //utf8 2 bytes: 1100xxxx 10xxxxxx
        //test if ucode smaller than binary: 100-00000000 = 0x400
        else if((ucode & 0xffffffff) < 0x400 )
        {
            //utf-8 has 2 bytes
            utf8[0]=0xC0 | (ucode >> 6) & 0xF;
            utf8[1]=0x80 | (ucode & 0x3F);
            count=2;
            return true;
        }

        //utf8 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
        //test if ucode smaller than binary: 1-00000000-00000000 = 0x10000
        else if((ucode & 0xffffffff) <  0x10000 )
        {
            //utf-8 has 3 bytes
            utf8[0]=0xE0 | (ucode >> 12) & 0xF;
            utf8[1]=0x80 | (ucode >> 6) & 0x3F;
            utf8[2]=0x80 | (ucode & 0x3F);
            count=3;
            return true;
        }

        //utf8 4 bytes: 1111xxxx 10xxxxxx 10xxxxxx 10xxxxxx
        //test if ucode smaller than binary: 1000000-00000000-00000000 = 0x400000
        else if((ucode & 0xFFFF0000) < 0x400000 )
        {
            //"utf-8 has 4 bytes
            utf8[0]=0xF0 | (ucode >> 18) & 0xF;
            utf8[1]=0x80 | (ucode >> 12) & 0x3F;
            utf8[2]=0x80 | (ucode >> 6) & 0x3F;
            utf8[3]=0x80 | (ucode & 0x3F);
            count=4;
            return true;
        }
        else
        {
            throw misc::exception("Exception on u2utf8 conversion.");
        }

    };//u2utf8

    //########################################################################
    bool utf82u(unsigned int& ucode, unsigned char utf8[4], unsigned short& count, bool throw_)
    {
        //1 byte encoding
        if((utf8[0] >> 7) == 0x0)
        {
            //unicode fill 1 byte
            ucode = 0x00000000;
            ucode |= (utf8[0] & 0x7F);
            count = 1;
            return true;
        }


        //2 bytes encoding
        if((utf8[0] >> 4) == 0xC)
        {
            //unicode fill 2 bytes
            if((utf8[1] >> 6) != 0x2)
            {
                if(throw_)
                    throw misc::exception("unicode bytes not valid");
                else
                {
                    count = 0;
                    return false;
                }
            }//if

            ucode = ((utf8[0] << 6) & 0x3C0) + (utf8[1] & 0x3F);
            count = 2;
            return true;
        }

        //3 bytes encoding
        if((utf8[0] >> 4) == 0xE)
        {
            //unicode fill 3 bytes
            if( (utf8[1] >> 6) != 0x2 ||
                (utf8[2] >> 6) != 0x2)
            {
                if(throw_)
                    throw misc::exception("unicode bytes not valid");
                else
                {
                    count = 0;
                    return false;
                }
            }//if

            ucode = ((utf8[0] << 12) & 0xF000) + ((utf8[1] << 6) & 0xFC0) + (utf8[2] & 0x3F);
            count = 3;
            return true;
        }

        //4 bytes encoding
        if((utf8[0] >> 4) == 0xF)
        {
            //ucode fill 4 bytes
            if( (utf8[1] >> 6) != 0x2 ||
                (utf8[2] >> 6) != 0x2 ||
                (utf8[3] >> 6) != 0x2)
            {
                if(throw_)
                    throw misc::exception("unicode bytes not valid");
                else
                {
                    count = 0;
                    return false;
                }
            }//if

            ucode = ((utf8[0] << 18) & 0x3C0000) + ((utf8[1] << 12) & 0x3F000) + ((utf8[2] << 6) & 0xFC0) + (utf8[3] & 0x3F);
            count = 4;
            return true;
        }


        count = 0;
        if((utf8[0] >> 6) == 0x2)
        {
            if(throw_)
                misc::exception("unicode intermediary byte");
            else
                return false;
        }

        if(throw_)
        {
            throw misc::exception("unicode byte invalid");
        }

        return false;
    };//utf82u

    //########################################################################
    bool u2utf8(unsigned int ucode, utf8string& utf8, unsigned short& count, bool throw_)
    {
        unsigned char uchar_[4];

        bool res = u2utf8(ucode, uchar_, count, throw_);

        for(unsigned short i=0; i<count; ++i)
        {
            utf8 += uchar_[i];
        }//for

        return res;
    };//u2utf8


    bool utf82u(unsigned int& ucode, const utf8string& utf8, size_t begin, unsigned short& count, bool throw_)
    {
        unsigned char uchar_[4]={0,0,0,0};
        size_t sz = utf8.size();
        size_t lim = begin + 4;
        size_t j=0;
        for(size_t i=begin; i < lim && i < sz; ++i, ++j )
        {
            uchar_[j] = utf8[i];
        }

        return utf82u(ucode, uchar_, count, throw_);
    };//utf82u

    //########################################################################


}//namespace


