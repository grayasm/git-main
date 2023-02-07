/*
Copyright (C) 2009 Mihai Vasilian
*/




#ifndef __strconv_hpp__
#define __strconv_hpp__



//c++
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>
#include <string>

//c
#include <stdio.h>

//exp
#include "string.hpp"




namespace stl
{


    //! convert ASCII to string
    stl::string from_ascii(const char* src);

    //! convert wide char seq. to string
    stl::string from_wide(const wchar_t* wstr);

    //! convert from std::[w]string to string
    stl::string from_string(const std::string& src);
    stl::string from_string(const std::wstring& wsrc);



    //! convert to ASCII
    std::string to_ascii( const wchar_t* wstr );
    std::string to_ascii( const std::string& str );
    std::string to_ascii( const std::wstring& wstr );

    //! convert to wide format
    std::wstring to_wide( const char* str );
    std::wstring to_wide( const std::string& str );
    std::wstring to_wide( const std::wstring& wstr );


    //! convert from value to string
    stl::string from_value( char cval );
    stl::string from_value( short ushval );
    stl::string from_value( unsigned short ushval );
    stl::string from_value( int ival );
    stl::string from_value( unsigned int uival );
    stl::string from_value( long lval );
    stl::string from_value( unsigned long ulval );
    stl::string from_value( float fval, unsigned short prec );
    stl::string from_value( double dval, unsigned short prec );
#ifdef _WIN64
	stl::string from_value(size_t ui64val);
#endif



    //! convert string to value
    bool to_value( const stl::string& src, char& value );
    bool to_value( const stl::string& valstr, short& value );
    bool to_value( const stl::string& valstr, unsigned short& value );
    bool to_value( const stl::string& valstr, int& value);
    bool to_value( const stl::string& valstr, unsigned int& value );
    bool to_value( const stl::string& valstr, long& value);
    bool to_value( const stl::string& valstr, unsigned long& value );
    bool to_value( const stl::string& valstr, float& value );
    bool to_value( const stl::string& valstr, double& value );
#ifdef _WIN64
	bool to_value(const stl::string& valstr, size_t& value);
#endif

    //! trimming methods
    void trim(stl::string& str, stl::char_t token=U(' '));
    void trim_left(stl::string& str, stl::char_t token=U(' '));
    void trim_right(stl::string& str, stl::char_t token=U(' '));

    //! case conversion methods
    std::string tolower( const std::string& str);
    stl::string toupper( const stl::string& str);

    //! string size
    size_t strlen(const char* str);
    size_t strlen(const wchar_t* wstr);



}//namespace






#endif //__strconv_hpp__
