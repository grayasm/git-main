/*
Copyright (C) 2014 Mihai Vasilian
*/



#ifndef __misctest_util_hpp__
#define __misctest_util_hpp__


#include "cpu_timer.hpp"
#include "stream.hpp"




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
            stl::cout << m_msg << " time: " << std::fixed << t0 << " sec";
        }
    }
private:
    const char* m_msg;
    bool m_print_time;
    sys::cpu_timer m_clck;
}; // class


#endif // __misctest_util_hpp__
