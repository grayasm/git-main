/*
Copyright (C) 2013 Mihai Vasilian
*/


#include "cpu_timer.hpp"
#include "exception.hpp"


namespace sys
{
	cpu_timer::cpu_timer()
	{
#if defined _WIN32
		// set frequency
		QueryPerformanceFrequency( &m_frequency );
		m_oneticktime = 1.0 / m_frequency.QuadPart;
#else // LINUX
		// nothing to initialize
#endif
	}

	void cpu_timer::start_clock()
	{
#if defined _WIN32
		m_starttime.QuadPart=0;
		QueryPerformanceCounter(&m_starttime);
#else // LINUX
		/* RUSAGE_SELF = 0, RUSAGE_CHILDREN = -1, RUSAGE_THREAD = 1*/
		if( getrusage(RUSAGE_SELF, &r_usage) == -1 )
			throw stl::exception("getrusage error");
#endif
	}

	double cpu_timer::end_clock()
	{
#if defined _WIN32
		m_endtime.QuadPart=0;
		QueryPerformanceCounter(&m_endtime);
		double difference = (double)(m_endtime.QuadPart - m_starttime.QuadPart);
		double timeinseconds = difference*m_oneticktime;
		return timeinseconds;
#else // LINUX
		struct rusage r_usage_end;
		if( getrusage(RUSAGE_SELF, &r_usage_end) == -1 )
			throw stl::exception("getrusage error");


		// resource metrics at beginning
		struct timeval ru_utime_beg = r_usage.ru_utime; // user time
		struct timeval ru_stime_beg = r_usage.ru_stime; // sys  time

		// resource metrics at this moment
		struct timeval ru_utime_end = r_usage_end.ru_utime;
		struct timeval ru_stime_end = r_usage_end.ru_stime;

		/* user time */
		__time_t        tv_sec_u  = ru_utime_end.tv_sec - ru_utime_beg.tv_sec; /* Seconds */
		__suseconds_t   tv_usec_u = ru_utime_end.tv_usec - ru_utime_beg.tv_usec; /* Microseconds.(long)*/

		/* system time */
		__time_t        tv_sec_s  = ru_stime_end.tv_sec - ru_stime_beg.tv_sec; /* Seconds */
		__suseconds_t   tv_usec_s = ru_stime_end.tv_usec - ru_stime_beg.tv_usec; /* Microseconds.(long)*/

		/* user + system */
		__time_t total_tv_sec = tv_sec_u + tv_sec_s;
		__suseconds_t total_tv_usec = tv_usec_u + tv_usec_s;

		double total_sec = (double)total_tv_sec + 1.e-6 * (double)total_tv_usec ;
		return total_sec;
#endif
	}

	double cpu_timer::get_clock()
	{
#if defined _WIN32
		QueryPerformanceCounter(&m_endtime);
		double difference = (double)(m_endtime.QuadPart - m_starttime.QuadPart);
		double timeinseconds = difference*m_oneticktime;
		return timeinseconds;
#else // LINUX
		return end_clock();
#endif
	}


	size_t cpu_timer::get_cpu_freq()
	{
#if defined _WIN32
		DWORD dwMHz;
		HKEY hKey;
		DWORD bufSize = sizeof(DWORD);
		long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
								   _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"),
								   0,
								   KEY_READ,
								   &hKey);
		if(lError == ERROR_SUCCESS)
		{
			lError = RegQueryValueEx(hKey, _T("~MHz"), NULL, NULL, (LPBYTE)&dwMHz, &bufSize);
			if(lError == ERROR_SUCCESS)
				return  static_cast<size_t>(dwMHz);
		}

		LARGE_INTEGER qwWait, qwStart, qwCurrent;
		QueryPerformanceCounter(&qwStart);
		QueryPerformanceFrequency(&qwWait);
		qwWait.QuadPart >>= 5;
		unsigned __int64 start = __rdtsc();
		do
		{
			QueryPerformanceCounter(&qwCurrent);
		} while(qwCurrent.QuadPart - qwStart.QuadPart < qwWait.QuadPart);
		double ddwMHz = ((__rdtsc() - start) << 5) / 1000000.0;

		return static_cast<size_t>(ddwMHz);
#else // LINUX
		return 0;
#endif
	}
}  // namespace

