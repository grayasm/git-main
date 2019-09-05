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



#ifndef __stream_hpp__
#define __stream_hpp__

#include <fstream>
#include <iostream>
#include <sstream>



namespace stl
{

#ifdef UNICODE
    typedef std::basic_filebuf<wchar_t>     filebuf ;
#else
    typedef std::basic_filebuf<char>        filebuf ;
#endif


#ifdef UNICODE
    typedef std::basic_ifstream<wchar_t>    ifstream  ;
#else
    typedef std::basic_ifstream<char>       ifstream  ;
#endif

#ifdef UNICODE
    typedef std::basic_ofstream<wchar_t>    ofstream ;
#else
    typedef std::basic_ofstream<char>       ofstream ;
#endif


#ifdef UNICODE
    typedef std::basic_fstream<wchar_t>     fstream ;
#else
    typedef std::basic_fstream<char>        fstream ;
#endif


#ifdef UNICODE
    typedef std::basic_streambuf<wchar_t>   streambuf ;
#else
    typedef std::basic_streambuf<char>      streambuf ;
#endif


#ifdef UNICODE
    typedef std::basic_istream<wchar_t>     istream ;
#else
    typedef std::basic_istream<char>        istream ;
#endif


#ifdef UNICODE
    typedef std::basic_ostream<wchar_t>     ostream ;
#else
    typedef std::basic_ostream<char>        ostream ;
#endif


#ifdef UNICODE
    typedef std::basic_iostream<wchar_t>    iostream ;
#else
    typedef std::basic_iostream<char>       iostream ;
#endif


#ifdef UNICODE
    typedef std::basic_stringbuf<wchar_t>   stringbuf ;
#else
    typedef std::basic_streambuf<char>      stringbuf ;
#endif


#ifdef UNICODE
    typedef std::basic_istringstream<wchar_t>   istringstream ;
#else
    typedef std::basic_istringstream<char>      istringstream ;
#endif


#ifdef UNICODE
    typedef std::basic_ostringstream<wchar_t>   ostringstream ;
#else
    typedef std::basic_ostringstream<char>      ostringstream ;
#endif



#ifdef UNICODE
    typedef std::basic_stringstream<wchar_t>    stringstream ;
#else
    typedef std::basic_stringstream<char>       stringstream ;
#endif




#ifdef UNICODE
    static stl::istream& cin  = std::wcin ;
    static stl::ostream& cout = std::wcout ;
    static stl::ostream& cerr = std::wcerr ;
    static stl::ostream& clog = std::wclog ;
#else
    static stl::istream& cin  = std::cin ;
    static stl::ostream& cout = std::cout ;
    static stl::ostream& cerr = std::cerr ;
    static stl::ostream& clog = std::clog ;
#endif





}  // namespace




#endif

