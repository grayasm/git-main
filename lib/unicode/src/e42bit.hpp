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




#ifndef __e42bit_hpp__
#define __e42bit_hpp__


#include "exception.hpp"

namespace unicode
{

    //! e42bit is internal byte encoding.
    //! This string representation can store up to 7 unsigned char (byte) for one unsigned int (32 bit) value.
    /*
      e42bit 8 bytes: 11111111 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
      e42bit 7 bytes: 11111110 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
      e42bit 6 bytes: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
      e42bit 5 bytes: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
      e42bit 4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
      e42bit 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
      e42bit 2 bytes: 110xxxxx 10xxxxxx
      e42bit 1 byte : 0xxxxxxx
    */

    typedef std::basic_string<unsigned char> e42bitstring;

    bool u2e42bit(unsigned int ucode, unsigned char e42bit[4], unsigned short& count, bool throw_);
    bool e42bit2u(unsigned int& ucode, unsigned char e42bit[4], unsigned short& count, bool throw_);
    bool u2e42bit(unsigned int ucode, e42bitstring& e42bit, unsigned short& count, bool throw_);
    bool e42bit2u(unsigned int& ucode, const e42bitstring& e42bit, size_t begin, unsigned short& count, bool throw_);




    //########################################################################


    //class e42bit_const_iterator
    //{
    //  Cnt* m_cnt;
    //  CIt m_it;

    //public:
    //  typedef std::basic_string<unsigned char> Cnt;
    //  typedef std::basic_string<unsigned char>::const_iterator CIt;

    //  ~e42bit_const_iterator()
    //  {
    //      m_cnt=0;
    //  };

    //  e42bit_const_iterator()
    //  {
    //      m_cnt=0;
    //  };

    //  e42bit_const_iterator(const e42bit_const_iterator& tc)
    //  {
    //      m_cnt = tc.m_cnt;
    //      m_it = tc.m_it;
    //  };

    //  e42bit_const_iterator(Cnt* cnt, const CIt& it)
    //      : m_cnt(cnt)
    //      , m_it(it)
    //  {
    //  };

    //  iterator& operator ++ ()
    //  {
    //      //next(it, range_end);
    //      return *this;
    //  }
    //  iterator operator ++ (int)
    //  {
    //      iterator temp = *this;
    //      next(it, range_end);
    //      return temp;
    //  }
    //  iterator& operator -- ()
    //  {
    //      prior(it, range_start);
    //      return *this;
    //  }
    //  iterator operator -- (int)
    //  {
    //      iterator temp = *this;
    //      prior(it, range_start);
    //      return temp;
    //  }

    //};


    //class e42bit_iterator{};
    //class e42bit_const_reverse_iterator{};
    //class e42bit_reverse_iterator{};



    //class e42bitstring : public std::basic_string<unsigned char>
    //{
    //public:
    //  typedef std::basic_string<unsigned char> Base;
    //  typedef Base::allocator_type allocator_type;
    //  typedef e42bit_const_iterator const_iterator;
    //  typedef Base::const_pointer const_pointer;
    //  typedef Base::const_reference const_reference;
    //  typedef e42bit_const_reverse_iterator const_reverse_iterator;
    //  typedef Base::difference_type difference_type;
    //  typedef e42bit_iterator iterator;
    //  typedef Base::npos npos;
    //  typedef Base::pointer pointer;
    //  typedef Base::reference reference;
    //  typedef e42bit_reverse_iterator reverse_iterator;
    //  typedef Base::size_type size_type;
    //  typedef Base::traits_type traits_type;
    //  typedef Base::value_type value_type;


    //  //
    //  const_iterator begin( ) const;
    //  iterator begin( );

    //  const_iterator end( ) const;
    //  iterator end( );

    //  const_reverse_iterator rbegin( ) const;
    //  reverse_iterator rbegin( );

    //  const_reverse_iterator rend( ) const;
    //  reverse_iterator rend( );

    //};
}//namespace




#endif//__e42bit_hpp__



