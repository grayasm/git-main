/*
Copyright (C) 2013 Mihai Vasilian
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

namespace sys
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
