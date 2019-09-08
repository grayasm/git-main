/*
  Copyright (C) 2019 Mihai Vasilian

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

#ifndef __file_hpp__
#define __file_hpp__

#include "string.hpp"


namespace sys
{
    class file
    {
    public:
        file();
        ~file();

        enum ScanEnum
        {
            S_TRAVERSE_NONE = 0<<0,     // default, does not scan subdirectories
            S_TRAVERSE      = 1<<0,     // scan each subdirectory
            S_HIDDEN_FILE   = 1<<1,     // show hidden files
            S_HIDDEN_DIR    = 1<<2,     // show hidden subdirectory
            S_DOT_DIRS      = 1<<3      // show '.' and '..' directories
        };

        typedef void(*scan_callback)(const stl::string& filepath, bool& abort);

        //  Scan an existing directory (no wildcards or regexp strings)
        void scandir(
            const char* dir,                // "D:\\Github\\Offsers\\"
            unsigned int flags,             // one or more from ScanEnum
            size_t max_depth,               // 0 for no traverse, -1 for maxim
            scan_callback cb);              // callback

    private:
        void scandir_(
            const char* dir,
            unsigned int flags,
            size_t max_depth,
            scan_callback cb,
            bool& aborting);

    private:
        size_t  m_depth;    // current traversing depth
    }; // class
}


#endif//__file_hpp__
