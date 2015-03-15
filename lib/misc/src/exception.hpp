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


#ifndef __exception_hpp__
#define __exception_hpp__


#include <exception>


namespace misc
{
    class exception : public std::exception
    {
    public:
        exception();                
        exception(const char* str);
        ~exception() throw();        
        const char* what() const throw();        
    private:
        char*   m_str;
    };
    
}  // namespace

#endif   /* __exception_hpp__ */
