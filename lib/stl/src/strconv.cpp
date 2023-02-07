/*
Copyright (C) 2009 Mihai Vasilian
*/



//Note: use explicit char/wchar_t in between #ifdef UNICODE .. #endif



//C
#include <malloc.h>
#include <stdlib.h>

//libutil
#include "strconv.hpp"
#include "string.hpp"



namespace stl
{

    stl::string from_ascii(const char* src)
    {
#ifdef UNICODE
        size_t strl=strlen(src) ;
        stl::string ret ;
        wchar_t* pwcs=NULL;
		pwcs=(wchar_t*) ::malloc((strl+1)*sizeof(wchar_t)) ;
        if(pwcs!=NULL)
        {
            mbstowcs(pwcs, src, strl);
            ret=stl::string(pwcs);
            delete pwcs ;
        }//if
        return ret ;
#else
        return stl::string(src);
#endif//UNICODE
    }//from_ascii




    stl::string from_wide(const wchar_t* wsrc)
    {
#if defined UNICODE
        return stl::string(wsrc) ;
#else
        size_t strl=wcslen(wsrc) ;
        stl::string ret;
        char* s=NULL;
		s=(char*) ::malloc((strl+1)*sizeof(char)) ;
        if(s!=NULL)
        {
            wcstombs(s,wsrc,strl);
            ret=stl::string(s);
            delete s;
        }
        return ret ;
#endif
    }//from_wide



    stl::string from_string(const std::string& src)
    {
#if defined UNICODE
        return from_ascii(src.c_str()) ;
#else
        return stl::string(src.c_str()) ;
#endif
    }//from_string




    stl::string from_string(const std::wstring& wsrc)
    {
#if defined UNICODE
        return stl::string(wsrc.c_str()) ;
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




    stl::string from_value( char cval )
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



    stl::string from_value( short shval )
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



    stl::string from_value( unsigned short ushval )
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


    stl::string from_value(int ival)
    {
        //UINT_MAX +4,294,967,295
#if defined UNICODE
        wchar_t buff[101];
        _snwprintf(buff,100,U("%d"),ival);
        return stl::string(buff);
#else
        char buff[101];
        snprintf(buff,100,U("%d"),ival);
        return stl::string(buff);
#endif
    }//from_value




    stl::string from_value(unsigned int uival)
    {
        //UINT_MAX +4,294,967,295
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff,100,U("%u"),uival);
        return stl::string(buff);
#else
        char buff[101];
        snprintf(buff,100,U("%u"),uival);
        return stl::string(buff);
#endif
    }//from_value




    stl::string from_value( long lval )
    {
        //ULONG_MAX (x64) +18,446,744,073,709,551,615
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff,100, U("%ld"),lval);
        return stl::string(buff);
#else
        char buff[101];
        snprintf(buff, 100, U("%ld"), lval);
        return stl::string(buff);
#endif
    }//from_value



    stl::string from_value( unsigned long ulval )
    {
#ifdef UNICODE
        wchar_t buff[101];
        _snwprintf(buff, 100, U("%lu"), ulval);
        return stl::string(buff);
#else
        char buff[101];
        snprintf(buff,100,U("%lu"),ulval);
        return stl::string(buff);
#endif
    }//from_value



    stl::string from_value( float fval, unsigned short prec )
    {
        //float 3.4E +/- 38 (7 digits) 4 bytes
#ifdef UNICODE
        wchar_t buff[351];
        wchar_t tmp[51];
        _snwprintf(tmp, 50, U("%%.%df"), prec);
        _snwprintf(buff, 350, tmp, fval);
        return stl::string(buff);
#else
        char buff[351];
        char tmp[51];
        snprintf(tmp, 50, U("%%.%df"), prec);
        snprintf(buff, 350, tmp, fval);
        return stl::string(buff);
#endif
    }//from_value


    stl::string from_value(double dval, unsigned short prec/*=6*/)
    {
        //double 1.7E +/- 308 (15 digits) 8 bytes
#ifdef UNICODE
        wchar_t buff[351];
        wchar_t tmp[21];
        _snwprintf(tmp,20, U("%s%u%s") , U("%."), prec, U("f"));
        _snwprintf(buff,350,tmp,dval);
        return stl::string(buff);
#else
        char buff[351];
        char tmp[21];
        snprintf(tmp,20, U("%s%u%s") , U("%."), prec, U("f"));
        snprintf(buff,350,tmp,dval);
        return stl::string(buff);
#endif
    }//from_value


#ifdef _WIN64
	stl::string from_value(size_t ui64val)
	{
#ifdef UNICODE
		wchar_t buff[101];
		_snwprintf(buff, 100, U("%lu"), ui64val);
		return stl::string(buff);
#else
		char buff[101];
		snprintf(buff, 100, U("%lu"), ui64val);
		return stl::string(buff);
#endif
	} // from_value
#endif

    bool to_value( const stl::string& src, char& cval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%c"), &cval) == 1;
#else
        return sscanf(src.c_str(), U("%c"), &cval) == 1;
#endif
    }//to_value



    bool to_value( const stl::string& src, short& shval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%d"), &shval) == 1;
#else
        return sscanf(src.c_str(), U("%hd"), &shval) == 1;
#endif
    }//to_value



    bool to_value( const stl::string& src, unsigned short& ushval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%u"), &ushval) == 1;
#else
        return sscanf(src.c_str(), U("%hu"), &ushval) == 1;
#endif
    }//to_value




    bool to_value( const stl::string& src, int& ival)
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%d"), &ival) == 1;
#else
        return sscanf(src.c_str(), U("%d"), &ival) == 1;
#endif
    }//to_value



    bool to_value( const stl::string& src, unsigned int& uival )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%u"), &uival) == 1;
#else
        return sscanf(src.c_str(), U("%u"), &uival) == 1;
#endif
    }//to_value



    bool to_value( const stl::string& src, long& lval)
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%ld"), &lval) == 1;
#else
        return sscanf(src.c_str(), U("%ld"), &lval) == 1;
#endif
    }//to_value


    bool to_value( const stl::string& src, unsigned long& ulval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%lu"), &ulval) == 1;
#else
        return sscanf(src.c_str(), U("%lu"), &ulval) == 1;
#endif
    }//to_value


    bool to_value( const stl::string& src, float& fval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(),U(""), &fval) == 1;
#else
        return sscanf(src.c_str(), U("%f"), &fval) == 1;
#endif
    }//to_value



    bool to_value( const stl::string& src, double& dval )
    {
        //0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
        return swscanf(src.c_str(), U("%lf"), &dval) == 1;
#else
        return sscanf(src.c_str(), U("%lf"), &dval) == 1;
#endif
    }//to_value


#ifdef _WIN64
	bool to_value(const stl::string& src, size_t& ui64val)
	{
		//0 for no conversion, -1 for error, n for n conversions;
#ifdef UNICODE
		return swscanf(src.c_str(), U("%lu"), &ui64val) == 1;
#else
		return sscanf(src.c_str(), U("%lu"), &ui64val) == 1;
#endif
	}
#endif


    void trim(stl::string& totrim, stl::char_t token/*=U(' ')*/)
    {
        stl::trim_left(totrim, token);
		stl::trim_right(totrim, token);
    }//trim


    void trim_left(stl::string& totrim, stl::char_t token/*=U(' ')*/)
    {
        size_t pos = totrim.find_first_not_of(token, 0);
        if(pos != stl::string::npos && pos > 0)
        {
            stl::string tmp = totrim.substr(pos, totrim.size()-pos);
            totrim=tmp;
        }
    }//trim_left

    void trim_right(stl::string& totrim, stl::char_t token/*=U(' ')*/)
    {
        size_t pos = totrim.find_last_not_of(token);
        if(pos != stl::string::npos && pos+1 < totrim.size())
        {
            stl::string tmp = totrim.substr(0, pos+1);
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

