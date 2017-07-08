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




#ifndef __strconv_hpp__
#define __strconv_hpp__



//c++
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>

//c
#include <stdio.h>

//exp
#include "string.hpp"




namespace misc
{


    //! convert ASCII to string
    misc::string from_ascii(const char* src);

    //! convert wide char seq. to string
    misc::string from_wide(const wchar_t* wstr);

    //! convert from std::[w]string to string
    misc::string from_string(const std::string& src);
    misc::string from_string(const std::wstring& wsrc);



    //! convert to ASCII
    std::string to_ascii( const wchar_t* wstr );
    std::string to_ascii( const std::string& str );
    std::string to_ascii( const std::wstring& wstr );

    //! convert to wide format
    std::wstring to_wide( const char* str );
    std::wstring to_wide( const std::string& str );
    std::wstring to_wide( const std::wstring& wstr );


    //! convert from value to string
    misc::string from_value( char cval );
    misc::string from_value( short ushval );
    misc::string from_value( unsigned short ushval );
    misc::string from_value( int ival );
    misc::string from_value( unsigned int uival );
    misc::string from_value( long lval );
    misc::string from_value( unsigned long ulval );
    misc::string from_value( float fval, unsigned short prec );
    misc::string from_value( double dval, unsigned short prec );
#ifdef _WIN64
	misc::string from_value(size_t ui64val);
#endif



    //! convert string to value
    bool to_value( const misc::string& src, char& value );
    bool to_value( const misc::string& valstr, short& value );
    bool to_value( const misc::string& valstr, unsigned short& value );
    bool to_value( const misc::string& valstr, int& value);
    bool to_value( const misc::string& valstr, unsigned int& value );
    bool to_value( const misc::string& valstr, long& value);
    bool to_value( const misc::string& valstr, unsigned long& value );
    bool to_value( const misc::string& valstr, float& value );
    bool to_value( const misc::string& valstr, double& value );
#ifdef _WIN64
	bool to_value(const misc::string& valstr, size_t& value);
#endif

    //! trimming methods
    void trim(misc::string& str, misc::char_t token=U(' '));
    void trim_left(misc::string& str, misc::char_t token=U(' '));
    void trim_right(misc::string& str, misc::char_t token=U(' '));

    //! case conversion methods
    std::string tolower( const std::string& str);
    misc::string toupper( const misc::string& str);

    //! string size
    size_t strlen(const char* str);
    size_t strlen(const wchar_t* wstr);



}//namespace






#endif //__strconv_hpp__
