/*
  Copyright (C) 2013 Mihai Vasilian

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


#ifndef __cpu_timer_hpp__
#define __cpu_timer_hpp__



// OS
#ifdef _WIN32
// WINDOWS
#include <windows.h>
#include <intrin.h>
#include <tchar.h>
#else
// LINUX
#include <stdlib.h>
#include <sys/resource.h>
#endif

namespace misc
{

    class cpu_timer
    {
    public:
        cpu_timer();
        void start_clock();
        double end_clock();
        double get_clock();
        static size_t get_cpu_freq();

    private:
#if defined _WIN32
        LARGE_INTEGER m_frequency;
        LARGE_INTEGER m_starttime;
        LARGE_INTEGER m_endtime;
        double m_oneticktime;
#else // LINUX
        /* indicate how much resource has been used */
        struct rusage r_usage;
#endif


    }; // class


}  // namespace

#endif //__cpu_timer_hpp__
