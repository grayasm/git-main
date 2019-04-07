/*
  Copyright (C) 2014 Mihai Vasilian

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



#ifndef __misctest_util_hpp__
#define __misctest_util_hpp__


#include "cpu_timer.hpp"




// Records the time and prints it with a message.
class time_printer
{
public:
    time_printer(const char* msg, bool print_time = true)
        : m_msg(msg)
        , m_print_time(print_time)
    {
        if(m_print_time)
            m_clck.start_clock();
    }
    ~time_printer()
    {
        if(m_print_time)
        {
            double t0 = m_clck.end_clock();
            misc::cout << m_msg << " time: " << std::fixed << t0 << " sec";
        }
    }
private:
    const char* m_msg;
    bool m_print_time;
    misc::cpu_timer m_clck;
}; // class


#endif // __misctest_util_hpp__
