/*
  Copyright (C) 2012 Mihai Vasilian

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



void testutf8()
{
    unsigned int ucode[] = {0x21, 0x41, 0x61, 129, 132, 162, 236, 251, 0x62, 0x32A, 0xAAF7, 0x3D5580};
    unsigned char utf8[4]={0,0,0,0};
    unsigned short count = 0;


    for(int i=0; i< sizeof(ucode)/sizeof(ucode[0]); ++i)
    {
        unicode::u2utf8(ucode[i], utf8, count, true);
        printf("\npt code[%d]= avem %d charactere", ucode[i], count);
        for(int j=0; j<count; ++j)
        {
            printf("\nchar[%d]=%c", j, utf8[j]);
        }
        printf("\n");

        unsigned int ucode2=0;
        unsigned short count2 = 0;
        unicode::utf82u(ucode2, utf8, count2, true);

        if(count2 != count)
            printf("\ndifferent counter");

        if(ucode2 != ucode[i])
            printf("\ndifferent unicode value");


        unicode::utf8string string;
        unicode::u2utf8(ucode[i], string, count, true);
        unicode::utf82u(ucode2, string, 0, count2, true);

        if(count2 != count)
            printf("\ndifferent counter");

        if(ucode2 != ucode[i])
            printf("\ndifferent unicode value");

    }//for
}


/*
  struct UChar
  {

  }


  class UChar
  {
  public:
  UChar(unsigned int unicode, )
  {

  }

  private:
  std::basic_string<unsigned char>  m_str;
  }
*/
