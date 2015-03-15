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



//Note: use explicit char/wchar_t in between #ifdef UNICODE .. #endif



//C
#include <malloc.h>
#include <stdlib.h>

//libutil
#include "strconv.hpp"
#include "string.hpp"



namespace misc
{

    misc::string from_ascii(const char* src)
    {
#ifdef UNICODE
        size_t strl=strlen(src) ;
        misc::string ret ;
        wchar_t* pwcs=NULL;
		pwcs=(wchar_t*) ::malloc((strl+1)*sizeof(wchar_t)) ;
        if(pwcs!=NULL)
        {
            mbstowcs(pwcs, src, strl);
            ret=misc::string(pwcs);
            delete pwcs ;
        }//if
        return ret ;
#else
        return misc::string(src);
#endif//UNICODE
    }//from_ascii




    misc::string from_wide(const wchar_t* wsrc)
    {
#if defined UNICODE
        return misc::string(wsrc) ;
#else
        size_t strl=wcslen(wsrc) ;
        misc::string ret;
        char* s=NULL;
		s=(char*) ::malloc((strl+1)*sizeof(char)) ;
        if(s!=NULL)
        {
            wcstombs(s,wsrc,strl);
            ret=misc::string(s);
            delete s;
        }
        return ret ;
#endif
    }//from_wide



    misc::string from_string(const std::string& src)
    {
#if defined UNICODE
        return from_ascii(src.c_str()) ;
#else
        return misc::string(src.c_str()) ;
#endif
    }//from_string




    misc::string from_string(const std::wstring& wsrc)
    {
#if defined UNICODE
        return misc::string(wsrc) ;
#else
        return from_wide(wsrc.c_str());
#endif
    }//from_string



    std::string to_ascii( const wchar_t* wstr )
    {
        std::string sstr ;
        size_t length = wcslen( wstr ) ;
		char* cstr = (char*) ::malloc( (length+1) * sizeof( char ) ) ;
        if( cstr != NULL )
        {
            /*size_t res = */wcstombs( cstr, wstr, length ) ;
            sstr = cstr ;
            free( cstr ) ;
        }//if
        return sstr ;
    }//to_ascii


    std::string to_ascii( const std::string& str )
    {
        return str ;
    }//to_ascii


    std::string to_ascii( const std::wstring& wstr )
    {
        std::string sstr ;
        size_t length = wstr.size() ;
		char* cstr = (char*) ::malloc( (length+1) * sizeof( char ) ) ;
        if( cstr != NULL )
        {
            size_t res = wcstombs( cstr, wstr.c_str() , length ) ;
            cstr[res]='\0';
            sstr = cstr ;
            free( cstr ) ;
        }//if
        return sstr ;
    }//to_ascii



    std::wstring to_wide( const char* str )
    {
        std::wstring wstr ;
        size_t length = strlen( str ) ;
		wchar_t* wcstr = (wchar_t*) ::malloc( (length+1) * sizeof( wchar_t ) ) ;
        if( wcstr != NULL )
        {
            size_t res = mbstowcs( wcstr, str, length ) ;
            wcstr[res]=U('\0');
            wstr = wcstr ;
            free( wcstr ) ;
        }
        return wstr ;
    }//to_wide


    std::wstring to_wide( const std::string& str )
    {
        std::wstring wstr ;
        size_t length = str.size() ;
		wchar_t* wcstr = (wchar_t*) ::malloc( (length+1) * sizeof( wchar_t ) ) ;
        if( wcstr != NULL )
        {
            size_t res = mbstowcs( wcstr, str.c_str() , length ) ;
            wcstr[res]=U('\0');
            wstr = wcstr ;
            free( wcstr ) ;
        }
        return wstr ;
    }//to_wide



    std::wstring to_wide( const std::wstring& wstr )
    {
        return wstr ;
    }//to_wide




    misc::string from_value( char cval )
    {
#ifdef UNICODE
        wchar_t buff[11];
        _snwprintf(buff, 10, U("%c"), cval);
        return buff;
#else
        char buff[11];
        snprintf(buff, 10, U("%c"), cval);
        return buff;
#endif
    }//from_value



    misc::string from_value( short shval )
    {
        //USHRT_MAX 65535
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff, 100, U("%d"), shval);
        return buff;
#else
        char buff[101];
        snprintf(buff, 100, U("%d"), shval);
        return buff;
#endif
    }//from_value



    misc::string from_value( unsigned short ushval )
    {
        //USHRT_MAX 65535
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff, 100, U("%u"), ushval);
        return buff ;
#else
        char buff[101];
        snprintf(buff, 100, U("%u"), ushval);
        return buff ;
#endif
    }//from_value


    misc::string from_value(int ival)
    {
        //UINT_MAX +4,294,967,295
#if defined UNICODE
        wchar_t buff[101];
        _snwprintf(buff,100,U("%d"),ival);
        return misc::string(buff);
#else
        char buff[101];
        snprintf(buff,100,U("%d"),ival);
        return misc::string(buff);
#endif
    }//from_value




    misc::string from_value(unsigned int uival)
    {
        //UINT_MAX +4,294,967,295
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff,100,U("%u"),uival);
        return misc::string(buff);
#else
        char buff[101];
        snprintf(buff,100,U("%u"),uival);
        return misc::string(buff);
#endif
    }//from_value




    misc::string from_value( long lval )
    {
        //ULONG_MAX (x64) +18,446,744,073,709,551,615
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff,100, U("%ld"),lval);
        return misc::string(buff);
#else
        char buff[101];
        snprintf(buff, 100, U("%ld"), lval);
        return misc::string(buff);
#endif
    }//from_value



    misc::string from_value( unsigned long ulval )
    {
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff, 100, U("%lu"), ulval);
        return misc::string(buff);
#else
        char buff[101];
        snprintf(buff,100,U("%lu"),ulval);
        return misc::string(buff);
#endif
    }//from_value



    misc::string from_value( float fval, unsigned short prec )
    {
        //float 3.4E +/- 38 (7 digits) 4 bytes
#ifdef UNICODE
        wchar_t buff[351];
        wchar_t tmp[51];
        _snwprintf(tmp, 50, U("%%.%df"), prec);
        _snwprintf(buff, 350, tmp, fval);
        return misc::string(buff);
#else
        char buff[351];
        char tmp[51];
        snprintf(tmp, 50, U("%%.%df"), prec);
        snprintf(buff, 350, tmp, fval);
        return misc::string(buff);
#endif
    }//from_value


    misc::string from_value(double dval, unsigned short prec/*=6*/)
    {
        //double 1.7E +/- 308 (15 digits) 8 bytes
#ifdef UNICODE
        wchar_t buff[351];
        wchar_t tmp[21];
        _snwprintf(tmp,20, U("%s%u%s") , U("%."), prec, U("f"));
        _snwprintf(buff,350,tmp,dval);
        return misc::string(buff);
#else
        char buff[351];
        char tmp[21];
        snprintf(tmp,20, U("%s%u%s") , U("%."), prec, U("f"));
        snprintf(buff,350,tmp,dval);
        return misc::string(buff);
#endif
    }//from_value



    bool to_value( const misc::string& src, char& cval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%c"), &cval) == 1;
#else
        return sscanf(src.c_str(), U("%c"), &cval) == 1;
#endif
    }//to_value



    bool to_value( const misc::string& src, short& shval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%d"), &shval) == 1;
#else
        return sscanf(src.c_str(), U("%hd"), &shval) == 1;
#endif
    }//to_value



    bool to_value( const misc::string& src, unsigned short& ushval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%u"), &ushval) == 1;
#else
        return sscanf(src.c_str(), U("%hu"), &ushval) == 1;
#endif
    }//to_value




    bool to_value( const misc::string& src, int& ival)
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%d"), &ival) == 1;
#else
        return sscanf(src.c_str(), U("%d"), &ival) == 1;
#endif
    }//to_value



    bool to_value( const misc::string& src, unsigned int& uival )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%u"), &uival) == 1;
#else
        return sscanf(src.c_str(), U("%u"), &uival) == 1;
#endif
    }//to_value



    bool to_value( const misc::string& src, long& lval)
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%ld"), &lval) == 1;
#else
        return sscanf(src.c_str(), U("%ld"), &lval) == 1;
#endif
    }//to_value


    bool to_value( const misc::string& src, unsigned long& ulval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%lu"), &ulval) == 1;
#else
        return sscanf(src.c_str(), U("%lu"), &ulval) == 1;
#endif
    }//to_value


    bool to_value( const misc::string& src, float& fval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(),U(""), &fval) == 1;
#else
        return sscanf(src.c_str(), U("%f"), &fval) == 1;
#endif
    }//to_value



    bool to_value( const misc::string& src, double& dval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%lf"), &dval) == 1;
#else
        return sscanf(src.c_str(), U("%lf"), &dval) == 1;
#endif
    }//to_value



    void trim(misc::string& totrim, misc::char_t token/*=U(' ')*/)
    {
        misc::trim_left(totrim, token);
		misc::trim_right(totrim, token);
    }//trim


    void trim_left(misc::string& totrim, misc::char_t token/*=U(' ')*/)
    {
        size_t pos = totrim.find_first_not_of(token, 0);
        if(pos != misc::string::npos && pos > 0)
        {
            misc::string tmp = totrim.substr(pos, totrim.size()-pos);
            totrim=tmp;
        }
    }//trim_left

    void trim_right(misc::string& totrim, misc::char_t token/*=U(' ')*/)
    {
        size_t pos = totrim.find_last_not_of(token);
        if(pos != misc::string::npos && pos+1 < totrim.size())
        {
            misc::string tmp = totrim.substr(0, pos+1);
            totrim=tmp;
        }
    }//trim_right



    std::string tolower( const std::string& src )
    {
        std::string dst(src) ;
        size_t size = src.length();
        for(size_t i=0; i<size; ++i)
        {
            dst[i] = static_cast<char>( ::tolower( static_cast<int>(src[i]) ) );
        }//for
        return dst;
    }//tolower


    std::string toupper( const std::string& src )
    {
        std::string dst(src) ;
        size_t size = src.length();
        for(size_t i=0; i<size; ++i)
        {
            dst[i] = static_cast<char>( ::toupper( static_cast<int>(src[i]) ) );
        }//for
        return dst;
    }//toupper


    size_t strlen(const char* str)
    {
        return ::strlen(str);
    }

    size_t strlen(const wchar_t* wstr)
    {
        return ::wcslen(wstr);
    }

}//namespace

